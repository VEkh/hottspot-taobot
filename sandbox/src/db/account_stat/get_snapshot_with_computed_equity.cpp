#ifndef DB__ACCOUNT_STAT_get_snapshot_with_computed_equity
#define DB__ACCOUNT_STAT_get_snapshot_with_computed_equity

#include "account_stat.h"                  // DB::AccountStat, query_result_t
#include "lib/formatted.cpp"               // Formatted
#include "result_to_account_snapshots.cpp" // result_to_account_snapshots
#include <iostream>                        // std::cout, std::endl
#include <libpq-fe.h>                      // PQescapeLiteral, PQfreemem
#include <regex>                           // std::regex, std::regex_search
#include <stdio.h>                         // snprintf
#include <string.h>                        // strlen
#include <string>                          // std::string, std::to_string

DB::AccountStat::account_snapshot_t
DB::AccountStat::get_snapshot_with_computed_equity(
    const get_snapshot_with_computed_equity_args_t args) {
  const double starting_from = args.starting_from;
  const std::string api_key_id = args.api_key_id;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  const char *query_format = R"(
    with day_original as (
      select
        api_key_id,
        equity,
        inserted_at,
        margin_buying_power
      from
        account_stats
      where
        api_key_id = %s
        and inserted_at >= to_timestamp(%f)
      order by
        inserted_at asc
      limit 1
    ),
    day_computed as (
      select
        coalesce(net.profit, 0.0) as profit
    from
      day_original
      left join lateral (
        select
          api_key_id,
          sum((current_profit * abs(open_order_quantity))) as profit
      from
        positions
      where
        opened_at between day_original.inserted_at and day_original.inserted_at + '1 day'::interval
        and api_key_id = day_original.api_key_id
      group by
        api_key_id) as net on net.api_key_id = day_original.api_key_id
    ),
    day_latest as (
      select
        extract(epoch from account_stats.inserted_at) as inserted_at_epoch
      from
        day_original
        join account_stats on account_stats.api_key_id = day_original.api_key_id
      where
        account_stats.inserted_at between day_original.inserted_at and day_original.inserted_at + '1 day'::interval
      order by
        account_stats.inserted_at desc
      limit 1
    ),
    day as (
      select
        day_original.api_key_id,
    (day_original.equity + day_computed.profit) as equity,
    (day_original.margin_buying_power) as original_margin_buying_power,
      day_latest.inserted_at_epoch
    from
      day_original
      join day_computed on true
      join day_latest on true
    ),
    latest as (
      select
        api_key_id,
        equity,
        extract(epoch from inserted_at) as inserted_at_epoch
      from
        account_stats
      where
        api_key_id = %s
      order by
        inserted_at desc
      limit 1
    )
    select
      coalesce(day.equity, latest.equity) as equity,
      coalesce(day.inserted_at_epoch, latest.inserted_at_epoch, 0.0) as timestamp_epoch,
      coalesce(day.original_margin_buying_power, 0.0) as original_margin_buying_power
    from
      latest
      left join day on day.api_key_id = latest.api_key_id
  )";

  const size_t query_l = strlen(query_format) +
                         2 * strlen(sanitized_api_key_id) +
                         std::to_string(starting_from).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, starting_from,
           sanitized_api_key_id);

  PQfreemem(sanitized_api_key_id);

  const query_result_t result = this->conn.exec(query, args.debug);

  std::list<account_snapshot_t> snapshots = result_to_account_snapshots(result);

  if (snapshots.empty()) {
    const std::string error_message = Formatted::error_message(
        std::string("DB__ACCOUNT_STAT_get_snapshot_with_computed_equity: No "
                    "account stats for ") +
        api_key_id);

    std::cout << error_message << std::endl;

    if (std::regex_search(result.error_message,
                          std::regex("statement timeout"))) {
      return get_snapshot_with_computed_equity(args);
    } else {
      return account_snapshot_t();
    }
  }

  return snapshots.front();
};

#endif

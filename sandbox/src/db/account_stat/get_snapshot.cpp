#ifndef DB__ACCOUNT_STAT_get_snapshot
#define DB__ACCOUNT_STAT_get_snapshot

#include "account_stat.h"                  // DB::AccountStat, query_result_t
#include "lib/formatted.cpp"               // Formatted
#include "result_to_account_snapshots.cpp" // result_to_account_snapshots
#include <iostream>                        // std::cout, std::endl
#include <libpq-fe.h>                      // PQescapeLiteral, PQfreemem
#include <stdio.h>                         // snprintf
#include <string.h>                        // strlen
#include <string>                          // std::string, std::to_string
#include <unistd.h>                        // usleep

DB::AccountStat::account_snapshot_t
DB::AccountStat::get_snapshot(const get_snapshot_args_t args) {
  const double starting_from = args.starting_from;
  const std::string api_key_id = args.api_key_id;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  const char *query_format = R"(
    select
      latest.api_key_id,
      latest.equity,
      latest.margin_buying_power,
      latest.margin_multiplier,
      max_equity.equity as max_equity,
      extract(epoch from max_equity.inserted_at) as max_equity_timestamp,
      min_equity.equity as min_equity,
      extract(epoch from min_equity.inserted_at) as min_equity_timestamp,
      original.equity as original_equity,
      original.margin_buying_power as original_margin_buying_power,
      extract(epoch from latest.inserted_at) as timestamp_epoch
    from (
      select
        *
      from
        account_stats
      where
        api_key_id = %s
      order by
        inserted_at desc
      limit 1) as latest
      join lateral (
        select
          api_key_id,
          equity,
          inserted_at
        from
          account_stats
        where
          api_key_id = latest.api_key_id
          and inserted_at >= to_timestamp(%f)
        order by
          equity desc
        limit 1) as max_equity on max_equity.api_key_id = latest.api_key_id
      join lateral (
        select
          api_key_id,
          equity,
          inserted_at
        from
          account_stats
        where
          api_key_id = latest.api_key_id
          and inserted_at >= to_timestamp(%f)
        order by
          equity asc
        limit 1) as min_equity on min_equity.api_key_id = latest.api_key_id
      join lateral (
        select
          api_key_id,
          equity,
          margin_buying_power
        from
          account_stats
        where
          api_key_id = latest.api_key_id
          and inserted_at >= to_timestamp(%f)
        order by
          inserted_at asc
        limit 1) as original on original.api_key_id = latest.api_key_id;
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         (3 * std::to_string(starting_from).size());

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, starting_from,
           starting_from, starting_from);

  PQfreemem(sanitized_api_key_id);

  const query_result_t result = this->conn.exec(query, args.debug);

  std::list<account_snapshot_t> snapshots = result_to_account_snapshots(result);

  if (snapshots.empty()) {
    const std::string error_message = Formatted::error_message(
        std::string("DB__ACCOUNT_STAT_get_snapshot: No account stats for ") +
        api_key_id);

    std::cout << error_message << std::endl;

    usleep(5e5);

    return get_snapshot(args);
  }

  return snapshots.front();
}

#endif

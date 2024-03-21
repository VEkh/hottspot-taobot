#ifndef DB__ACCOUNT_STAT_get_daily_snapshots
#define DB__ACCOUNT_STAT_get_daily_snapshots

#include "account_stat.h" // DB::AccountStat, get_daily_snapshots_args_t, query_result_t
#include "result_to_account_snapshots.cpp" // result_to_account_snapshots
#include <libpq-fe.h>                      // PQescapeLiteral, PQfreemem
#include <list>                            // std::list
#include <stdio.h>                         // snprintf
#include <string.h>                        // strlen
#include <string>                          // std::string

std::list<DB::AccountStat::account_snapshot_t>
DB::AccountStat::get_daily_snapshots(const get_daily_snapshots_args_t args) {
  const std::string api_key_id = args.api_key_id;
  std::string end_at = "max(inserted_at)";
  std::string start_at = "now() - '1 week'::interval";

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  if (!args.end_at.empty()) {
    char *sanitized_end_at = PQescapeLiteral(
        this->conn.conn, args.end_at.c_str(), args.end_at.size());

    end_at = std::string(sanitized_end_at) + "::date";

    PQfreemem(sanitized_end_at);
  }

  if (args.start_at == "earliest") {
    start_at = "min(inserted_at)";
  } else if (!args.start_at.empty()) {
    char *sanitized_start_at = PQescapeLiteral(
        this->conn.conn, args.start_at.c_str(), args.start_at.size());

    start_at = std::string(sanitized_start_at) + "::date";

    PQfreemem(sanitized_start_at);
  }

  const char *query_format = R"(
    select
      extract(epoch from trading_days.day) as timestamp_epoch,
      trading_days.api_key_id,
      latest.equity,
      latest.margin_buying_power,
      latest.margin_multiplier,
      max_equity.equity as max_equity,
      extract(epoch from max_equity.inserted_at) as max_equity_timestamp,
      min_equity.equity as min_equity,
      extract(epoch from min_equity.inserted_at) as min_equity_timestamp,
      original.equity as original_equity,
      original.margin_buying_power as original_margin_buying_power
    from (
      select
        %s as api_key_id,
        date_timestamp as day
      from (
        select
          generate_series(range.begin_date, range.end_date, '1 day'::interval) date_timestamp
        from (
          select
            api_key_id,
            date_trunc('day', %s) as begin_date,
            date_trunc('day', %s) as end_date
          from
            account_stats
          where
            api_key_id = %s
          group by
            api_key_id) as range) as full_date_range
      where
        extract(isodow from full_date_range.date_timestamp) < 6) as trading_days
      join lateral (
        select
          *
        from
          account_stats
        where
          api_key_id = trading_days.api_key_id
          and inserted_at >= trading_days.day
          and inserted_at <(trading_days.day + interval '1 day')
        order by
          inserted_at desc
        limit 1) as latest on latest.api_key_id = trading_days.api_key_id
      join lateral (
        select
          api_key_id,
          equity,
          inserted_at
        from
          account_stats
        where
          api_key_id = trading_days.api_key_id
          and inserted_at >= trading_days.day
          and inserted_at <(trading_days.day + interval '1 day')
        order by
          equity desc
        limit 1) as max_equity on max_equity.api_key_id = trading_days.api_key_id
      and max_equity.inserted_at >= trading_days.day
      and max_equity.inserted_at <(trading_days.day + interval '1 day')
    join lateral (
      select
        api_key_id,
        equity,
        inserted_at
      from
        account_stats
      where
        api_key_id = trading_days.api_key_id
        and inserted_at >= trading_days.day
        and inserted_at <(trading_days.day + interval '1 day')
      order by
        equity asc
      limit 1) as min_equity on min_equity.api_key_id = trading_days.api_key_id
      and min_equity.inserted_at >= trading_days.day
      and min_equity.inserted_at <(trading_days.day + interval '1 day')
    join lateral (
      select
        api_key_id,
        equity,
        inserted_at,
        margin_buying_power
      from
        account_stats
      where
        api_key_id = trading_days.api_key_id
        and inserted_at >= trading_days.day
        and inserted_at <(trading_days.day + interval '1 day')
      order by
        inserted_at asc
      limit 1) as original on original.api_key_id = trading_days.api_key_id
      and original.inserted_at >= trading_days.day
      and original.inserted_at <(trading_days.day + interval '1 day')
  )";

  const size_t query_l = strlen(query_format) +
                         2 * strlen(sanitized_api_key_id) + start_at.size() +
                         end_at.size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, start_at.c_str(),
           end_at.c_str(), sanitized_api_key_id);

  PQfreemem(sanitized_api_key_id);

  const query_result_t result = this->conn.exec(query, args.debug);

  return result_to_account_snapshots(result);
}

#endif

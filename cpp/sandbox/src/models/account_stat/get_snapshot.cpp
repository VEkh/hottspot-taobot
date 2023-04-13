#ifndef DB__ACCOUNT_STAT_get_snapshot
#define DB__ACCOUNT_STAT_get_snapshot

#include "account_stat.h"                 // DB::AccountStat, query_result_t
#include "result_to_account_snapshot.cpp" // result_to_account_snapshot
#include <libpq-fe.h>                     // PQescapeLiteral, PQfreemem
#include <stdio.h>                        // snprintf
#include <string.h>                       // strlen
#include <string>                         // std::string, std::to_string

DB::AccountStat::account_snapshot_t
DB::AccountStat::get_snapshot(const get_snapshot_args_t args) {
  const double session_started_at = args.session_started_at;
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
      session_max.equity as session_max_equity,
      extract(epoch from session_max.inserted_at) as session_max_equity_timestamp,
      session_original.equity as session_original_equity,
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
        limit 1) as original on original.api_key_id = latest.api_key_id
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
        limit 1) as session_max on session_max.api_key_id = latest.api_key_id
      join lateral (
        select
          api_key_id,
          equity
        from
          account_stats
        where
          api_key_id = latest.api_key_id
          and inserted_at >= to_timestamp(%f)
        order by
          inserted_at asc
        limit 1) as session_original on session_original.api_key_id = latest.api_key_id;
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         (3 * std::to_string(starting_from).size()) +
                         (2 * std::to_string(session_started_at).size());

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, starting_from,
           starting_from, starting_from, session_started_at,
           session_started_at);

  PQfreemem(sanitized_api_key_id);

  const query_result_t result = this->conn.exec(query, args.debug);

  return result_to_account_snapshot(result);
};

#endif

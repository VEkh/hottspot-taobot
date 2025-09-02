#ifndef DB__MARKET_SESSION_get_stats
#define DB__MARKET_SESSION_get_stats

#include "market_session.h" // DB::MarketSession, get_stats_args_t, query_result_t, market_session_get_stats_t
#include "result_to_market_session_stats.cpp" // result_to_market_session_stats
#include <libpq-fe.h>                         // PQescapeLiteral, PQfreemem
#include <stdio.h>                            // snprintf
#include <string.h>                           // strlen
#include <string>                             // std::string, std::to_string

DB::MarketSession::market_session_stats_t
DB::MarketSession::get_stats(const get_stats_args_t args) {
  const double ref_epoch = args.ref_epoch;
  const std::string symbol = args.symbol;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    with stats_data as (
      select
        open_period,
        ((100.0 * (high - low)) / open) as range_open_percent,
        ((100.0 * (warm_up_high - warm_up_low)) / warm_up_open) as warm_up_range_open_percent
      from
        market_sessions
      where
        symbol = %s
        and (high + low + open != 0)
        and (warm_up_high + warm_up_low + warm_up_open != 0)
        and upper(open_period) < to_timestamp(%f)
    ),
    stats as (
      select
        percentile_cont(0.5) within group (order by range_open_percent asc) as range_open_percent_median,
        stddev(range_open_percent) as range_open_percent_std_dev,
        percentile_cont(0.5) within group (order by warm_up_range_open_percent asc) as warm_up_range_open_percent_median,
        stddev(warm_up_range_open_percent) as warm_up_range_open_percent_std_dev
      from
        stats_data
    )
    select
      *,
      (range_open_percent_median - range_open_percent_std_dev) as range_open_percent_normalization_base,
      (warm_up_range_open_percent_median - warm_up_range_open_percent_std_dev) as warm_up_range_open_percent_normalization_base
    from
      stats
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(ref_epoch).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol, ref_epoch);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, args.debug);

  return this->result_to_market_session_stats(result);
}

#endif

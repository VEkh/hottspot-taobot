#ifndef DB__QUOTE_get_avg_one_sec_variances
#define DB__QUOTE_get_avg_one_sec_variances

#include "quote.h" // DB::Quote, avg_one_sec_variances_t
#include "result_to_avg_one_sec_variances.cpp" // result_to_avg_one_sec_variances
#include <libpq-fe.h>                          // PQescapeLiteral, PQfreemem
#include <stdio.h>                             // snprintf
#include <string.h>                            // strlen
#include <string>                              // std::string, std::to_string

DB::Quote::avg_one_sec_variances_t DB::Quote::get_avg_one_sec_variances(
    const get_avg_one_sec_variances_args_t args) {
  const bool debug = args.debug;
  const double timestamp_upper_bound = args.timestamp_upper_bound;
  const int timestamp_lower_bound_interval_days =
      args.timestamp_lower_bound_interval_days;
  const std::string symbol = args.symbol;

  const char *query_format = R"(
    select
      latest_avg.avg_one_sec_variance as latest,
      limited_agg.avg as running,
      latest_avg.symbol
    from (
      select
        avg_one_sec_variance,
        symbol
      from
        avg_one_sec_variances
      where
        symbol = %s
        and timestamp <= to_timestamp(%f)
      order by
        timestamp desc
      limit 1) as latest_avg
      join lateral (
        select
          avg(avg_one_sec_variance)
        from
          avg_one_sec_variances
        where
          symbol = latest_avg.symbol
          and timestamp >= to_timestamp(%f) - '%i days'::interval
          and timestamp <= to_timestamp(%f)) as limited_agg on true
  )";

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const size_t query_l =
      strlen(query_format) + strlen(sanitized_symbol) +
      3 * (std::to_string(timestamp_upper_bound).size()) +
      std::to_string(timestamp_lower_bound_interval_days).size();

  char query[query_l];
  snprintf(query, query_l, query_format, sanitized_symbol,
           timestamp_upper_bound, timestamp_upper_bound,
           timestamp_lower_bound_interval_days, timestamp_upper_bound);

  query_result_t result = this->conn.exec(query, args.debug);

  PQfreemem(sanitized_symbol);

  return result_to_avg_one_sec_variances(result);
}

#endif

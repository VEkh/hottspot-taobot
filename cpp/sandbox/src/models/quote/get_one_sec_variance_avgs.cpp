#ifndef DB__QUOTE_get_one_sec_variance_avgs
#define DB__QUOTE_get_one_sec_variance_avgs

#include "quote.h" // DB::Quote, one_sec_variance_avgs_t
#include "result_to_one_sec_variance_avgs.cpp" // result_to_one_sec_variance_avgs
#include <libpq-fe.h>                          // PQescapeLiteral, PQfreemem
#include <stdio.h>                             // snprintf
#include <string.h>                            // strlen
#include <string>                              // std::string, std::to_string

DB::Quote::one_sec_variance_avgs_t DB::Quote::get_one_sec_variance_avgs(
    const get_one_sec_variance_avgs_args_t args) {
  const bool debug = args.debug;
  const double timestamp_upper_bound = args.timestamp_upper_bound;
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
          limited.symbol,
          avg(limited.avg_one_sec_variance) as avg
        from (
          select
            avg_one_sec_variance,
            symbol
          from
            avg_one_sec_variances
          where
            symbol = latest_avg.symbol
            and timestamp <= to_timestamp(%f)
          order by
            timestamp desc
          limit 500000) as limited
      group by
        limited.symbol) as limited_agg on limited_agg.symbol = latest_avg.symbol;
  )";

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(timestamp_upper_bound).size() +
                         std::to_string(timestamp_upper_bound).size();

  char query[query_l];
  snprintf(query, query_l, query_format, sanitized_symbol,
           timestamp_upper_bound, timestamp_upper_bound);

  query_result_t result = this->conn.exec(query, debug);

  PQfreemem(sanitized_symbol);

  return result_to_one_sec_variance_avgs(result);
}

#endif

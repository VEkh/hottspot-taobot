#ifndef DB__PRICE_ACTION_get_stats
#define DB__PRICE_ACTION_get_stats

#include "price_action.h"      // DB::PriceAction, query_result_t
#include "result_to_stats.cpp" // result_to_stats
#include <libpq-fe.h>          // PQescapeLiteral, PQfreemem
#include <stdio.h>             // snprintf
#include <string.h>            // strlen
#include <string>              // std::to_string

DB::PriceAction::price_action_stats_t
DB::PriceAction::get_stats(const get_stats_args_t args) {
  const double end_at = args.end_at;
  const int time_range_weeks = args.time_range_weeks;

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  std::string start_at_clause = "";

  if (time_range_weeks) {
    const char *format =
        "and opened_at >= (to_timestamp(%f) - '%i weeks'::interval)";

    const size_t size = strlen(format) + std::to_string(end_at).size() +
                        std::to_string(time_range_weeks).size();

    char clause[size];

    snprintf(clause, size, format, end_at, time_range_weeks);

    start_at_clause = clause;
  }

  const char *query_format = R"(
    select
      symbol,
      coalesce(avg(range_open_percent), 0.0) as "avg",
      coalesce(stddev(range_open_percent), 0.0) as "std"
    from
      price_actions
    where
      symbol = %s
      and opened_at < to_timestamp(%f)
      %s
    group by
      symbol;
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(end_at).size() + start_at_clause.size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol, end_at,
           start_at_clause.c_str());

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, this->debug);

  return result_to_stats(result);
}

#endif

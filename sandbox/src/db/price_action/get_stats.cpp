#ifndef DB__PRICE_ACTION_get_stats
#define DB__PRICE_ACTION_get_stats

#include "price_action.h"      // DB::PriceAction, query_result_t
#include "result_to_stats.cpp" // result_to_stats
#include <libpq-fe.h>          // PQescapeLiteral, PQfreemem
#include <stdio.h>             // snprintf
#include <string.h>            // strlen
#include <string>              // std::to_string

DB::PriceAction::price_action_stats_t
DB::PriceAction::get_stats(const double end_at) {
  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

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
    group by
      symbol;
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(end_at).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol, end_at);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, this->debug);

  return result_to_stats(result);
}

#endif

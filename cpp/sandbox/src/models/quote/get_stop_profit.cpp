#ifndef DB__QUOTE_get_stop_profit
#define DB__QUOTE_get_stop_profit

#include "quote.h"                   // DB::Quote
#include "result_to_stop_profit.cpp" // result_to_stop_profit
#include <libpq-fe.h>                // PQescapeLiteral, PQfreemem
#include <stdio.h>                   // snprintf
#include <string.h>                  // strlen
#include <string>                    // std::string

double DB::Quote::get_stop_profit(const std::string symbol,
                                  const bool debug = false) {
  // TODO: The below api_key_id should be of a backtest that regularly
  // generates these positions.
  const char *query_format = R"(
    select
      avg(max_profit) as stop_profit
    from
      positions
    where
      api_key_id = 'PKB5FJN28HVP0TNZV00B'
      and symbol = %s
    group by
      symbol;
  )";

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol);

  char query[query_l];
  snprintf(query, query_l, query_format, sanitized_symbol);

  query_result_t result = this->conn.exec(query, debug);

  PQfreemem(sanitized_symbol);

  return result_to_stop_profit(result);
}

#endif

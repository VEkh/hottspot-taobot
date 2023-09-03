#ifndef DB__MARGIN_RATE_get
#define DB__MARGIN_RATE_get

#include "margin_rate.h"             // DB::MarginRate, query_result_t
#include "result_to_margin_rate.cpp" // result_to_margin_rate
#include <libpq-fe.h>                // PQescapeLiteral, PQfreemem
#include <stdio.h>                   // snprintf
#include <string.h>                  // strlen
#include <string>                    // std::string

DB::MarginRate::margin_rate_t DB::MarginRate::get(const std::string symbol,
                                                  const bool debug = false) {
  const char *query_format = "select * from margin_rates where symbol = %s";

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, debug);

  return result_to_margin_rate(result);
}

#endif

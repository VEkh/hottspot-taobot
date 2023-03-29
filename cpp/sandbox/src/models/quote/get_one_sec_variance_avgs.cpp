#ifndef DB__QUOTE_get_one_sec_variance_avgs
#define DB__QUOTE_get_one_sec_variance_avgs

#include "quote.h" // DB::Quote, one_sec_variance_avgs_t
#include "result_to_one_sec_variance_avgs.cpp" // result_to_one_sec_variance_avgs
#include <libpq-fe.h>                          // PQescapeLiteral, PQfreemem
#include <stdio.h>                             // snprintf
#include <string.h>                            // strlen
#include <string>                              // std::string

DB::Quote::one_sec_variance_avgs_t
DB::Quote::get_one_sec_variance_avgs(const std::string symbol,
                                     const bool debug = false) {
  const char *query_format = R"(
    select * from limited_one_sec_variance_running_averages
    where symbol=%s
  )";

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol);

  char query[query_l];
  snprintf(query, query_l, query_format, sanitized_symbol);

  query_result_t result = this->conn.exec(query, debug);

  PQfreemem(sanitized_symbol);

  return result_to_one_sec_variance_avgs(result);
}

#endif

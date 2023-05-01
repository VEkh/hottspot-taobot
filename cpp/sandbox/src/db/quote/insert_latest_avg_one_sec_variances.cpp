#ifndef DB__QUOTE_insert_latest_avg_one_sec_variances
#define DB__QUOTE_insert_latest_avg_one_sec_variances

#include "quote.h"    // DB::Quote, query_result_t
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <list>       // std::list
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string

void DB::Quote::insert_latest_avg_one_sec_variances(
    const std::list<std::string> &symbols) {
  std::string sanitized_symbols;

  for (const std::string symbol : symbols) {
    char *sanitized_symbol =
        PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

    if (!sanitized_symbols.empty()) {
      sanitized_symbols += ", ";
    }

    sanitized_symbols += std::string(sanitized_symbol);
    PQfreemem(sanitized_symbol);
  }

  const char *query_format =
      "select insert_latest_avg_one_sec_variances(array[%s]::text[]) as result";

  const size_t query_l = strlen(query_format) + sanitized_symbols.size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbols.c_str());

  this->conn.exec(query);
}

#endif

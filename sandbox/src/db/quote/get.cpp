#ifndef DB__QUOTE_get
#define DB__QUOTE_get

#include "quote.h"              // DB::Quote, quote_t, query_result_t
#include "result_to_quotes.cpp" // result_to_quotes
#include <libpq-fe.h>           // PQescapeLiteral, PQfreemem
#include <list>                 // std::list
#include <math.h>               // INFINITY
#include <stdio.h>              // snprintf
#include <string.h>             // strlen
#include <string>               // std::string, std::to_string

std::list<DB::Quote::quote_t> DB::Quote::get(const std::string symbol,
                                             const double limit = INFINITY) {

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const std::string limit_clause =
      limit == INFINITY ? "" : " limit " + std::to_string((int)limit);

  const char *query_format = R"(
    select
      ask, bid, symbol, extract(epoch from timestamp) as timestamp_epoch
    from quotes
    where symbol=%s
    order by timestamp asc
    %s
  )";

  const size_t query_l =
      strlen(query_format) + strlen(sanitized_symbol) + limit_clause.size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol,
           limit_clause.c_str());

  query_result_t query_result = this->conn.exec(query);
  PQfreemem(sanitized_symbol);

  std::list<quote_t> result = result_to_quotes(query_result);

  return result;
}

#endif

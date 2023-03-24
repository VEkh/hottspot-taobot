#ifndef DB__QUOTE_get_last
#define DB__QUOTE_get_last

/*
 * DB::Quote
 * get_last_args_t
 * quote_t
 * query_result_t
 */
#include "quote.h"

#include "result_to_collection.cpp" // result_to_collection
#include <libpq-fe.h>               // PQescapeLiteral, PQfreemem
#include <stdio.h>                  // snprintf
#include <string.h>                 // strlen
#include <string>                   // std::string, std::to_string
#include <vector>                   // std::vector

std::vector<DB::Quote::quote_t> DB::Quote::get_last(get_last_args_t args) {
  const bool debug = args.debug;
  const int limit = args.limit;
  const std::string symbol = args.symbol;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), sizeof(symbol.c_str()));

  const char *query = R"(
    select
      ask, bid, symbol, extract(epoch from timestamp) as timestamp
    from quotes
    where
      symbol=%s
      and id in (
        select id from quotes
        where symbol=%s
        order by timestamp desc
        limit %i
      )
    order by timestamp asc
  )";

  const size_t query_l = strlen(query) + strlen(sanitized_symbol) +
                         strlen(sanitized_symbol) +
                         std::to_string(limit).size();

  char formatted_query[query_l];

  snprintf(formatted_query, query_l, query, sanitized_symbol, sanitized_symbol,
           limit);

  query_result_t query_result = this->conn.exec(formatted_query, debug);
  PQfreemem(sanitized_symbol);

  std::vector<quote_t> result = result_to_collection(query_result);

  return result;
}

#endif

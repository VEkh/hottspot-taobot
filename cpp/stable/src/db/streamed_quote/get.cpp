#ifndef DB__STREAMED_QUOTE_get
#define DB__STREAMED_QUOTE_get

#include "result_to_quote.cpp" // result_to_quote
#include "streamed_quote.h"    // DB::StreamedQuote, get_args_t, query_result_t
#include <libpq-fe.h>          // PQescapeLiteral, PQfreemem
#include <stdio.h>             // snprintf
#include <string.h>            // strlen

DB::StreamedQuote::quote_t DB::StreamedQuote::get(const get_args_t args) {
  const std::string symbol = args.symbol;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    select
      ask,
      bid,
      symbol,
      extract(epoch from updated_at) as timestamp
    from
      streamed_quotes
    where
      symbol = %s
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol);
  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol);
  PQfreemem(sanitized_symbol);

  query_result_t result = this->conn.exec(query, args.debug);

  return result_to_quote(result);
}

#endif

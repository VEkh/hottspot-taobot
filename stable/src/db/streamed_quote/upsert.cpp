#ifndef DB__STREAMED_QUOTE_upsert
#define DB__STREAMED_QUOTE_upsert

#include "lib/utils/time.cpp" // ::utils::time_
#include "streamed_quote.h"   // DB::StreamedQuote
#include <libpq-fe.h>         // PQescapeLiteral, PQfreemem
#include <stdio.h>            // snprintf
#include <string.h>           // strlen
#include <string>             // std::string, std::to_string

void DB::StreamedQuote::upsert(const upsert_args_t args) {
  const double ask = args.ask;
  const double bid = args.bid;
  const std::string symbol = args.symbol;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    insert into streamed_quotes(ask, bid, symbol)
      values (%f, %f, %s)
    on conflict (symbol)
      do update set
        ask = excluded.ask, bid = excluded.bid, updated_at = now()
  )";

  const size_t query_l = strlen(query_format) + std::to_string(ask).size() +
                         std::to_string(bid).size() + symbol.size();

  char query[query_l];
  snprintf(query, query_l, query_format, ask, bid, sanitized_symbol);
  PQfreemem(sanitized_symbol);

  this->conn.exec(query, args.debug);
}

#endif

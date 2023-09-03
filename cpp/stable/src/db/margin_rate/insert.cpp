#ifndef DB__MARGIN_RATE_insert
#define DB__MARGIN_RATE_insert

#include "margin_rate.h" // DB::MarginRate
#include <libpq-fe.h>    // PQescapeLiteral, PQfreemem
#include <stdio.h>       // snprintf
#include <string.h>      // strlen
#include <string>        // std::string, std::to_string

void DB::MarginRate::insert(const insert_args_t args) {
  const double multiplier = args.multiplier;
  const std::string symbol = args.symbol;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    insert into margin_rates(multiplier, symbol)
      values (%f, upper(%s))
    on conflict (multiplier, symbol)
      do nothing
  )";

  const size_t query_l = strlen(query_format) +
                         std::to_string(multiplier).size() +
                         strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, multiplier, sanitized_symbol);

  PQfreemem(sanitized_symbol);

  this->conn.exec(query, args.debug);
}

#endif

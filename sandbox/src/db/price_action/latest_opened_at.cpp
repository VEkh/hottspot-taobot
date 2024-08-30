#ifndef DB__PRICE_ACTION_latest_opened_at
#define DB__PRICE_ACTION_latest_opened_at

#include "price_action.h" // DB::PriceAction, query_result_t
#include <libpq-fe.h>     // PQescapeLiteral, PQfreemem
#include <stdio.h>        // snprintf
#include <string.h>       // strlen
#include <string>         // std::stod

double DB::PriceAction::latest_opened_at() {
  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const char *query_format = R"(
    select
      extract(epoch from opened_at) as latest_opened_at
    from
      price_actions
    where
      symbol = %s
    order by
      opened_at desc
    limit 1;
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, this->debug);

  return result.tuples.empty() ? 0.0 : std::stod(result.tuples.back());
}

#endif

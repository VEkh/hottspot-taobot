#ifndef DB__PRICE_ACTION_upsert
#define DB__PRICE_ACTION_upsert

#include "price_action.h" // DB::PriceAction, upsert_args_t
#include <libpq-fe.h>     // PQescapeLiteral, PQfreemem
#include <stdio.h>        // snprintf
#include <string.h>       // strlen
#include <string>         // std::string, std::to_string

void DB::PriceAction::upsert(candle_t &candle) {
  const double closed_at = candle.closed_at;
  const double opened_at = candle.opened_at;
  const double range_open_percent = candle.range_open_percent();

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const char *query_format = R"(
    insert into price_actions(closed_at, opened_at, range_open_percent, symbol)
      values (to_timestamp(%f), to_timestamp(%f), %f, %s)
    on conflict (closed_at, opened_at, symbol)
      do update set
        range_open_percent = excluded.range_open_percent;
  )";

  const size_t query_l =
      strlen(query_format) + std::to_string(closed_at).size() +
      std::to_string(opened_at).size() +
      std::to_string(range_open_percent).size() + strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, closed_at, opened_at,
           range_open_percent, sanitized_symbol);

  PQfreemem(sanitized_symbol);

  this->conn.exec(query, this->debug);
}

#endif

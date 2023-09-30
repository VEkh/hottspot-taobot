#ifndef DB__CANDLE_upsert
#define DB__CANDLE_upsert

#include "candle.h"   // DB::Candle
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::to_string

void DB::Candle::upsert(const candle_t candle, const bool debug = false) {
  const char *query_format = R"(
    insert into candles(close, closed_at, duration_minutes, high, low, open, opened_at, symbol)
      values (%f, to_timestamp(%f), %i, %f, %f, %f, to_timestamp(%f), %s)
    on conflict (duration_minutes, opened_at, symbol)
      do update set close = excluded.close, closed_at = excluded.closed_at, high = excluded.high, low = excluded.low, open = excluded.open, updated_at = now()
  )";

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, candle.symbol.c_str(), candle.symbol.size());

  const size_t query_l =
      strlen(query_format) + std::to_string(candle.close).size() +
      std::to_string(candle.closed_at).size() +
      std::to_string(this->duration_minutes).size() +
      std::to_string(candle.high).size() + std::to_string(candle.low).size() +
      std::to_string(candle.open).size() +
      std::to_string(candle.opened_at).size() + strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, candle.close, candle.closed_at,
           this->duration_minutes, candle.high, candle.low, candle.open,
           candle.opened_at, sanitized_symbol);

  PQfreemem(sanitized_symbol);

  this->conn.exec(query, debug);
}

#endif

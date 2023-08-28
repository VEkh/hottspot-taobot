#ifndef DB__FIVE_MIN_CANDLES_upsert
#define DB__FIVE_MIN_CANDLES_upsert

#include "five_min_candles.h" // DB::FiveMinCandles
#include <libpq-fe.h>         // PQescapeLiteral, PQfreemem
#include <stdio.h>            // snprintf
#include <string.h>           // strlen
#include <string>             // std::to_string

void DB::FiveMinCandles::upsert(const candle_t candle,
                                const bool debug = false) {
  const char *query_format = R"(
    insert into five_min_candles(close, closed_at, high, low, open, opened_at, symbol)
      values (%f, to_timestamp(%f), %f, %f, %f, to_timestamp(%f), %s)
    on conflict (opened_at, symbol)
      do update set close = excluded.close, closed_at = excluded.closed_at, high = excluded.high, low = excluded.low, open = excluded.open, updated_at = now()
  )";

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, candle.symbol.c_str(), candle.symbol.size());

  const size_t query_l =
      strlen(query_format) + std::to_string(candle.close).size() +
      std::to_string(candle.closed_at).size() +
      std::to_string(candle.high).size() + std::to_string(candle.low).size() +
      std::to_string(candle.open).size() +
      std::to_string(candle.opened_at).size() + strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, candle.close, candle.closed_at,
           candle.high, candle.low, candle.open, candle.opened_at,
           sanitized_symbol);

  PQfreemem(sanitized_symbol);

  this->conn.exec(query, debug);
}

#endif

#ifndef DB__CANDLE_get_default_build_start_at
#define DB__CANDLE_get_default_build_start_at

#include "candle.h"   // DB::Candle, query_result_t
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::stod, std::to_string

double DB::Candle::get_default_build_start_at(const bool debug = false) {
  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const char *query_format = R"(
    select
      extract(epoch from coalesce(candles.max_opened_at, first_quotes.first_timestamp)) as start_at
    from (
      select
        max(opened_at) as max_opened_at
      from
        candles
      where
        symbol = %s
        and duration_minutes = %i) as candles
      right join lateral (
        select
          min("timestamp") as first_timestamp
        from
          quotes
        where
          symbol = %s) as first_quotes on true
  )";

  const size_t query_size = strlen(query_format) +
                            2 * strlen(sanitized_symbol) +
                            std::to_string(this->duration_minutes).size();

  char query[query_size];

  snprintf(query, query_size, query_format, sanitized_symbol, duration_minutes,
           sanitized_symbol);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, debug);

  return result.tuples.empty() ? 0 : std::stod(result.tuples.back());
}

#endif

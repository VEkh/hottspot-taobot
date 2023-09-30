#ifndef DB__CANDLE_get_latest_quotes
#define DB__CANDLE_get_latest_quotes

#include "candle.h"   // DB::Candle
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <list>       // std::list
#include <stdio.h>    // snprintf
#include <string.h>   // strlen

std::list<DB::Candle::quote_t>
DB::Candle::get_latest_quotes(const bool debug = false) {
  const char *query_format = R"(
    with latest_opened_at as (
      select
        coalesce(candles.max_opened_at, first_quotes.first_timestamp) as value
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
    )
    select
      quotes.*,
      extract(epoch from quotes."timestamp") as timestamp_epoch
    from
      quotes
    where
      quotes.symbol = %s
      and quotes."timestamp" >=(
        select
          value
        from
          latest_opened_at)
    order by
      quotes."timestamp" asc
  )";

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const size_t query_l = strlen(query_format) + 3 * strlen(sanitized_symbol) +
                         std::to_string(this->duration_minutes).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol,
           this->duration_minutes, sanitized_symbol, sanitized_symbol);

  PQfreemem(sanitized_symbol);

  const query_result_t query_result = this->conn.exec(query, debug);

  return this->db_quote.result_to_quotes(query_result);
}

#endif

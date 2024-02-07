#ifndef DB__CANDLE_get_latest
#define DB__CANDLE_get_latest

#include "candle.h"              // DB::Candle, candle_t
#include "result_to_candles.cpp" // result_to_candles
#include <libpq-fe.h>            // PQescapeLiteral, PQfreemem
#include <list>                  // std::list
#include <stdio.h>               // snprintf
#include <string.h>              // strlen
#include <string>                // std::to_string

std::list<DB::Candle::candle_t>
DB::Candle::get_latest(const get_latest_args_t args) {
  const double end_at_epoch = args.end_at_epoch;
  const double start_at_epoch = args.start_at_epoch;

  const char *query_format = R"(
    with latest_candles as (
      select
        *,
        extract (epoch from closed_at) as closed_at_epoch,
        extract (epoch from opened_at) as opened_at_epoch
      from
        candles
      where
        symbol = %s
        and duration_minutes = %i
        and opened_at >= to_timestamp(%f)
        and closed_at <= to_timestamp(%f)
      order by
        closed_at desc
    )
    select
      *
    from
      latest_candles
    order by
      closed_at asc;
  )";

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(this->duration_minutes).size() +
                         std::to_string(start_at_epoch).size() +
                         std::to_string(end_at_epoch).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol,
           this->duration_minutes, start_at_epoch, end_at_epoch);

  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, args.debug);

  return result_to_candles(result);
}

#endif

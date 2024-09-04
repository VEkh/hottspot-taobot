#ifndef DB__CANDLE_get_build_quotes
#define DB__CANDLE_get_build_quotes

#include "candle.h"   // DB::Candle, get_build_quotes_args_t
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <list>       // std::list
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::to_string

std::list<DB::Candle::quote_t>
DB::Candle::get_build_quotes(const get_build_quotes_args_t args) {
  const double end_at = args.end_at;
  const double start_at = args.start_at;
  const int limit = args.limit;

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  const char *query_format = R"(
      select
        quotes.*,
        extract(epoch from quotes."timestamp") as timestamp_epoch
      from
        quotes
      where
        quotes.symbol = %s
        and quotes."timestamp" >= to_timestamp(%f)
        and quotes."timestamp" < date_trunc('minute', to_timestamp(%f))
      order by
        quotes."timestamp" asc
      limit %i
    )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(start_at).size() +
                         std::to_string(end_at).size() +
                         std::to_string(limit).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol, start_at, end_at,
           limit);

  PQfreemem(sanitized_symbol);

  const query_result_t query_result = this->conn.exec(query, args.debug);

  return this->db_quote.result_to_quotes(query_result);
}

#endif

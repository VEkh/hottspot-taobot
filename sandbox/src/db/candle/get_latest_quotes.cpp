#ifndef DB__CANDLE_get_latest_quotes
#define DB__CANDLE_get_latest_quotes

#include "candle.h"   // DB::Candle, time_range_args_t
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <list>       // std::list
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string, std::to_string

std::list<DB::Candle::quote_t>
DB::Candle::get_latest_quotes(const time_range_args_t args) {
  std::string query;

  char *sanitized_symbol = PQescapeLiteral(
      this->conn.conn, this->symbol.c_str(), this->symbol.size());

  if (args.end_at || args.start_at) {
    const std::string end_at_clause =
        args.end_at ? "and quotes.\"timestamp\" < to_timestamp(" +
                          std::to_string(args.end_at) + ")"
                    : "";

    const std::string start_at_clause =
        args.start_at ? "and quotes.\"timestamp\" >= to_timestamp(" +
                            std::to_string(args.start_at) + ")"
                      : "";

    const char *time_range_query_format = R"(
      select
        quotes.*,
        extract(epoch from quotes."timestamp") as timestamp_epoch
      from
        quotes
      where
        quotes.symbol = %s
        %s
        %s
      order by
        quotes."timestamp" asc
    )";

    const size_t time_range_query_l =
        strlen(time_range_query_format) + strlen(sanitized_symbol) +
        start_at_clause.size() + end_at_clause.size();

    char time_range_query[time_range_query_l];

    snprintf(time_range_query, time_range_query_l, time_range_query_format,
             sanitized_symbol, start_at_clause.c_str(), end_at_clause.c_str());

    query = time_range_query;
  } else {
    const char *dynamic_query_format = R"(
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
        and quotes."timestamp" < date_trunc('minute', now())
      order by
        quotes."timestamp" asc
    )";

    const size_t dynamic_query_l =
        strlen(dynamic_query_format) + 3 * strlen(sanitized_symbol) +
        std::to_string(this->duration_minutes).size();

    char dynamic_query[dynamic_query_l];

    snprintf(dynamic_query, dynamic_query_l, dynamic_query_format,
             sanitized_symbol, this->duration_minutes, sanitized_symbol,
             sanitized_symbol);

    query = dynamic_query;
  }

  PQfreemem(sanitized_symbol);

  const query_result_t query_result =
      this->conn.exec(query.c_str(), args.debug);

  return this->db_quote.result_to_quotes(query_result);
}

#endif

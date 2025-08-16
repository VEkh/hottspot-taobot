#ifndef DB__MARKET_SESSION_upsert
#define DB__MARKET_SESSION_upsert

#include "market_session.h" // DB::MarketSession, market_session_t
#include <libpq-fe.h>       // PQescapeLiteral, PQfreemem
#include <stdio.h>          // snprintf
#include <string.h>         // strlen
#include <string>           // std::to_string

void DB::MarketSession::upsert(const market_session_t args, const bool debug) {
  const double close = args.close;
  const double closed_at = args.closed_at;
  const double high = args.high;
  const double low = args.low;
  const double open = args.open;
  const double opened_at = args.opened_at;
  const std::string symbol = args.symbol;
  const double warm_up_close = args.warm_up_close;
  const double warm_up_closed_at = args.warm_up_closed_at;
  const double warm_up_high = args.warm_up_high;
  const double warm_up_low = args.warm_up_low;
  const double warm_up_open = args.warm_up_open;
  const double warm_up_opened_at = args.warm_up_opened_at;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    insert into market_sessions(
      close,
      high,
      low,
      open,
      open_period,
      symbol,
      warm_up_close,
      warm_up_high,
      warm_up_low,
      warm_up_open,
      warm_up_period
    )
      values (
        %f,
        %f,
        %f,
        %f,
        tstzrange(to_timestamp(%f), to_timestamp(%f), '()'),
        %s,
        %f,
        %f,
        %f,
        %f,
        tstzrange(to_timestamp(%f), to_timestamp(%f), '()')
      )
    on conflict (symbol, open_period, warm_up_period)
      do update set
        close = excluded.close,
        high = excluded.high,
        low = excluded.low,
        open = excluded.open,
        warm_up_close = excluded.warm_up_close,
        warm_up_high = excluded.warm_up_high,
        warm_up_low = excluded.warm_up_low,
        warm_up_open = excluded.warm_up_open;
  )";

  const size_t query_l =
      strlen(query_format) + std::to_string(close).size() +
      std::to_string(high).size() + std::to_string(low).size() +
      std::to_string(open).size() + std::to_string(opened_at).size() +
      std::to_string(closed_at).size() + strlen(sanitized_symbol) +
      std::to_string(warm_up_close).size() +
      std::to_string(warm_up_high).size() + std::to_string(warm_up_low).size() +
      std::to_string(warm_up_open).size() +
      std::to_string(warm_up_opened_at).size() +
      std::to_string(warm_up_closed_at).size();

  char query[query_l];

  snprintf(query, query_l, query_format, close, high, low, open, opened_at,
           closed_at, sanitized_symbol, warm_up_close, warm_up_high,
           warm_up_low, warm_up_open, warm_up_opened_at, warm_up_closed_at);

  PQfreemem(sanitized_symbol);

  this->conn.exec(query, debug);
}

#endif

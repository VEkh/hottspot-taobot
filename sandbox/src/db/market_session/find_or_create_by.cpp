#ifndef DB__MARKET_SESSION_find_or_create_by
#define DB__MARKET_SESSION_find_or_create_by

#include "market_session.h" // DB::MarketSession, find_or_create_by_args_t, query_result_t, market_session_t
#include "result_to_market_sessions.cpp" // result_to_market_sessions
#include "upsert.cpp"                    // upsert
#include <libpq-fe.h>                    // PQescapeLiteral, PQfreemem
#include <stdio.h>                       // snprintf
#include <string.h>                      // strlen
#include <string>                        // std::string, std::to_string

DB::MarketSession::market_session_t
DB::MarketSession::find_or_create_by(const find_or_create_by_args_t args) {
  const double closed_at = args.closed_at;
  const double opened_at = args.opened_at;
  const double warm_up_period_seconds = args.warm_up_period_seconds;
  const std::string symbol = args.symbol;

  const double warm_up_closed_at = opened_at + warm_up_period_seconds;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *find_query_format = R"(
    select
      close,
      extract(epoch from upper(open_period)) as closed_at,
      high,
      id,
      low,
      open,
      extract(epoch from lower(open_period)) as opened_at,
      symbol,
      warm_up_close,
      extract(epoch from upper(warm_up_period)) as warm_up_closed_at,
      warm_up_high,
      warm_up_low,
      warm_up_open,
      extract(epoch from lower(warm_up_period)) as warm_up_opened_at
    from
      market_sessions
    where
      symbol = %s
      and open_period = tstzrange(to_timestamp(%f), to_timestamp(%f), '()')
      and warm_up_period = tstzrange(to_timestamp(%f), to_timestamp(%f), '()');
  )";

  const size_t find_query_l =
      strlen(find_query_format) + strlen(sanitized_symbol) +
      2 * std::to_string(opened_at).size() + std::to_string(closed_at).size() +
      std::to_string(warm_up_closed_at).size();

  char find_query[find_query_l];

  snprintf(find_query, find_query_l, find_query_format, sanitized_symbol,
           opened_at, closed_at, opened_at, warm_up_closed_at);

  PQfreemem(sanitized_symbol);

  query_result_t get_query_result = this->conn.exec(find_query, args.debug);

  if (get_query_result.tuples.empty()) {
    upsert(
        {
            .close = 0.0,
            .closed_at = args.closed_at,
            .high = 0.0,
            .low = 0.0,
            .open = 0.0,
            .opened_at = args.opened_at,
            .symbol = args.symbol,
            .warm_up_close = 0.0,
            .warm_up_closed_at = args.opened_at + args.warm_up_period_seconds,
            .warm_up_high = 0.0,
            .warm_up_low = 0.0,
            .warm_up_open = 0.0,
            .warm_up_opened_at = args.opened_at,
        },
        args.debug);

    return find_or_create_by(args);
  }

  std::list<market_session_t> results =
      result_to_market_sessions(get_query_result);

  return results.front();
}

#endif

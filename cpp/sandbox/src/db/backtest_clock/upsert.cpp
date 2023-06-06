#ifndef DB__BACKTEST_CLOCK_upsert
#define DB__BACKTEST_CLOCK_upsert

#include "backtest_clock.h" // DB::BacktestClock
#include <libpq-fe.h>       // PQescapeLiteral, PQfreemem
#include <stdio.h>          // snprintf
#include <string.h>         // strlen
#include <string>           // std::string, std::to_string

void DB::BacktestClock::upsert(const upsert_args_t args) {
  const double set_to = args.set_to;
  const std::string api_key_id = args.api_key_id;
  const std::string symbol = args.symbol;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    insert into backtest_clocks(api_key_id, set_to, symbol)
      values (%s, to_timestamp(%f), %s)
      on conflict (api_key_id, symbol)
        do update set
          set_to = excluded.set_to
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         std::to_string(set_to).size() +
                         strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, set_to,
           sanitized_symbol);

  PQfreemem(sanitized_api_key_id);
  PQfreemem(sanitized_symbol);

  this->conn.exec(query, args.debug);
}

#endif

#ifndef DB__MARKET_SESSION_PERFORMANCE_upsert
#define DB__MARKET_SESSION_PERFORMANCE_upsert

#include "market_session_performance.h" // DB::MarketSessionPerformance, upsert_args_t
#include <libpq-fe.h>                   // PQescapeLiteral, PQfreemem
#include <stdio.h>                      // snprintf
#include <string.h>                     // strlen
#include <string>                       // std::to_string

void DB::MarketSessionPerformance::upsert(const upsert_args_t args) {
  const std::string env = args.env;
  const int market_session_id = args.market_session_id;
  const double max_drawdown_percent = args.max_drawdown_percent;
  const double profit_loss_percent = args.profit_loss_percent;
  const int time_to_max_drawdown_seconds = args.time_to_max_drawdown_seconds;
  const int trade_setup_id = args.trade_setup_id;

  char *sanitized_env =
      PQescapeLiteral(this->conn.conn, env.c_str(), env.size());

  const char *query_format = R"(
    insert into market_session_performances(
      env,
      market_session_id,
      max_drawdown_percent,
      profit_loss_percent,
      time_to_max_drawdown_seconds,
      trade_setup_id
    )
      values (
        %s::jsonb,
        %d,
        %f,
        %f,
        %d,
        %d
      )
    on conflict (market_session_id, trade_setup_id)
      do update set
        env = excluded.env,
        max_drawdown_percent = excluded.max_drawdown_percent,
        profit_loss_percent = excluded.profit_loss_percent,
        time_to_max_drawdown_seconds = excluded.time_to_max_drawdown_seconds;
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_env) +
                         std::to_string(market_session_id).size() +
                         std::to_string(max_drawdown_percent).size() +
                         std::to_string(profit_loss_percent).size() +
                         std::to_string(time_to_max_drawdown_seconds).size() +
                         std::to_string(trade_setup_id).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_env, market_session_id,
           max_drawdown_percent, profit_loss_percent,
           time_to_max_drawdown_seconds, trade_setup_id);

  PQfreemem(sanitized_env);

  this->conn.exec(query, args.debug);
}

#endif

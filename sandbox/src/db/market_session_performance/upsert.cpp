#ifndef DB__MARKET_SESSION_PERFORMANCE_upsert
#define DB__MARKET_SESSION_PERFORMANCE_upsert

#include "market_session_performance.h" // DB::MarketSessionPerformance, market_session_performance_t
#include <stdio.h>                      // snprintf
#include <string.h> // strlen
#include <string>   // std::to_string

void DB::MarketSessionPerformance::upsert(
    const market_session_performance_t args, const bool debug = false) {
  const int market_session_id = args.market_session_id;
  const double profit_loss_percent = args.profit_loss_percent;
  const int trade_setup_id = args.trade_setup_id;

  const char *query_format = R"(
    insert into market_session_performances(
      market_session_id,
      profit_loss_percent,
      trade_setup_id
    )
      values (
        %d,
        %f,
        %d
      )
    on conflict (market_session_id, trade_setup_id)
      do update set
        profit_loss_percent = excluded.profit_loss_percent;
  )";

  const size_t query_l = strlen(query_format) +
                         std::to_string(market_session_id).size() +
                         std::to_string(profit_loss_percent).size() +
                         std::to_string(trade_setup_id).size();

  char query[query_l];

  snprintf(query, query_l, query_format, market_session_id, profit_loss_percent,
           trade_setup_id);

  this->conn.exec(query, debug);
}

#endif

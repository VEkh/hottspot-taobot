#ifndef DB__MARKET_SESSION_PERFORMANCE_H
#define DB__MARKET_SESSION_PERFORMANCE_H

#include "db/utils/utils.h" // DB::Utils
#include "lib/pg/pg.h"      // Pg
#include <math.h>           // INFINITY
#include <string>           // std::string

namespace DB {
class MarketSessionPerformance {
public:
  struct market_session_performance_t {
    double drawdown_percent = 0.0;
    int market_session_id;
    double max_drawdown_percent = 0.0;
    double max_equity = -INFINITY;
    double max_equity_at = 0.0;
    double profit_loss_percent = 0.0;
    double time_to_max_drawdown_seconds = 0.0;
    int trade_setup_id;
  };

  struct upsert_args_t {
    bool debug = false;
    std::string env;
    int id;
    int market_session_id;
    double max_drawdown_percent = 0.0;
    double profit_loss_percent;
    double time_to_max_drawdown_seconds = 0.0;
    int trade_setup_id;
  };

  MarketSessionPerformance(){};
  MarketSessionPerformance(Pg);

  void upsert(const upsert_args_t);

private:
  using query_result_t = Pg::query_result_t;

  DB::Utils db_utils;
  Pg conn;
};
}; // namespace DB

#endif

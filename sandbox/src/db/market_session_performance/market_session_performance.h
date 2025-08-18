#ifndef DB__MARKET_SESSION_PERFORMANCE_H
#define DB__MARKET_SESSION_PERFORMANCE_H

#include "db/utils/utils.h" // DB::Utils
#include "lib/pg/pg.h"      // Pg

namespace DB {
class MarketSessionPerformance {
public:
  struct market_session_performance_t {
    int id;
    int market_session_id;
    double profit_loss_percent;
    int trade_setup_id;
  };

  MarketSessionPerformance(){};
  MarketSessionPerformance(Pg);

  void upsert(const market_session_performance_t, const bool);

private:
  using query_result_t = Pg::query_result_t;

  DB::Utils db_utils;
  Pg conn;
};
}; // namespace DB

#endif

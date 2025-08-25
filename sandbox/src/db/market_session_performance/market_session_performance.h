#ifndef DB__MARKET_SESSION_PERFORMANCE_H
#define DB__MARKET_SESSION_PERFORMANCE_H

#include "db/utils/utils.h" // DB::Utils
#include "lib/pg/pg.h"      // Pg
#include <string>           // std::string

namespace DB {
class MarketSessionPerformance {
public:
  struct upsert_args_t {
    bool debug = false;
    std::string env;
    int id;
    int market_session_id;
    double profit_loss_percent;
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

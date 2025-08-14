#ifndef DB__TRADE_SETUP_H
#define DB__TRADE_SETUP_H

#include "db/utils/utils.h" // DB::Utils
#include "lib/pg/pg.h"      // Pg
#include <list>             // std::list

namespace DB {
class TradeSetup {
public:
  struct find_or_create_by_args_t {
    bool debug = false;
    int reverse_percentile_id;
    int stop_profit_id;
  };

  struct trade_setup_t {
    int id;
    int priority;
    int reverse_percentile_id;
    int stop_profit_id;
  };

  TradeSetup(){};
  TradeSetup(Pg);

  trade_setup_t find_or_create_by(const find_or_create_by_args_t);

private:
  using query_result_t = Pg::query_result_t;

  DB::Utils db_utils;
  Pg conn;

  std::list<trade_setup_t> result_to_trade_setups(const query_result_t &);

  void upsert(const find_or_create_by_args_t);
};
}; // namespace DB

#endif

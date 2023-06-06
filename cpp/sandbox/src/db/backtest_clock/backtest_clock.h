#ifndef DB__BACKTEST_CLOCK_H
#define DB__BACKTEST_CLOCK_H

#include "lib/pg/pg.cpp" // Pg
#include <list>          // std::list
#include <string>        // std::string

namespace DB {
class BacktestClock {
public:
  struct backtest_clock_t {
    std::string api_key_id;
    double set_to;
    std::string symbol;
  };

  struct get_all_args_t {
    std::string api_key_id;
    double set_to;
    bool debug = false;
  };

  struct upsert_args_t {
    std::string api_key_id;
    double set_to;
    std::string symbol;
    bool debug = false;
  };

  BacktestClock(){};
  BacktestClock(Pg c) : conn(c){};

  std::list<backtest_clock_t> get_all(const get_all_args_t);
  void upsert(const upsert_args_t);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;

  std::list<backtest_clock_t> result_to_backtest_clocks(const query_result_t &);
};
} // namespace DB

#endif

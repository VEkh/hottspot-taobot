#ifndef ALPACA__TAO_BOT_BACKTEST_H
#define ALPACA__TAO_BOT_BACKTEST_H

#include "lib/pg/pg.cpp" // Pg
#include "types.cpp"     // Global::t
#include <map>           // std::map
#include <string>        // std::string

namespace Alpaca {
class TaoBotBacktest {
public:
  using account_snapshot_t = Global::t::account_snapshot_t;

  struct config_t {
    double account_margin_multiplier = 0.00;
    double account_starting_equity = 0.00;
    std::string api_key;
    std::string api_key_id;
    double start_epoch = 0;
  } config;

  TaoBotBacktest(){};
  TaoBotBacktest(Pg, std::map<std::string, std::string>);

  bool is_active = false;
  int slow_query_countdown = 0;

  bool should_exec_slow_query();

  void upsert_account_stat(const double);

private:
  DB::AccountStat db_account_stat;

  static constexpr int SLOW_QUERY_EVERY = 100;

  std::map<std::string, std::string> flags;

  void load_config();
};
} // namespace Alpaca

#endif

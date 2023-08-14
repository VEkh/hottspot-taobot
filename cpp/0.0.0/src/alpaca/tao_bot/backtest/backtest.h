#ifndef ALPACA__TAO_BOT_BACKTEST_H
#define ALPACA__TAO_BOT_BACKTEST_H

#include "alpaca/types.cpp"                 // Alpaca::t
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/quote/quote.cpp"               // DB::Quote
#include "db/utils/utils.cpp"               // DB::Utils
#include "lib/pg/pg.cpp"                    // Pg
#include "types.cpp"                        // Global::t
#include <map>                              // std::map
#include <string>                           // std::string
#include <time.h>                           // time

namespace Alpaca {
class TaoBotBacktest {
public:
  using account_snapshot_t = Global::t::account_snapshot_t;
  using order_action_t = Alpaca::t::order_action_t;
  using order_status_t = Alpaca::t::order_status_t;
  using order_t = Alpaca::t::order_t;
  using quote_t = Alpaca::t::quote_t;

  // NOTES:
  // * clock_sync - Ensures that all tradeable assets' clocks are synced.
  //                However, it slows backtest runs. If set to `false`, spurious
  //                account max stop losses may trigger. A `false` setting
  //                should therefore accompany an `account_max_stop_loss`
  //                setting of `false`.
  struct config_t {
    double account_margin_multiplier = 0.00;
    bool account_max_stop_loss = true;
    double account_starting_equity = 0.00;
    std::string api_key;
    std::string api_key_id;
    bool clock_sync = true;
    double end_epoch = 0;
    int late_start_seconds = 6; // Production's average latency
    double start_epoch = 0;
  } config;

  struct init_args_t {
    Pg conn;
    std::map<std::string, std::string> flags;
    std::string symbol;
  };

  TaoBotBacktest(){};
  TaoBotBacktest(const init_args_t);

  bool is_active = false;
  int slow_query_countdown = 0;
  long int started_at = time(nullptr);
  std::string symbol;

  bool has_reached_end(const double);
  bool should_exec_slow_query(const double);

  int next_day_market_open_epoch(const double);

  std::string fetch_order(const order_t *, const quote_t &);
  std::string subscribe_clock(const bool);

  void place_order(const long int, order_t *);
  void publish_clock(const double, const bool);
  void upsert_account_stat(const double, const bool);

private:
  DB::AccountStat db_account_stat;
  DB::Quote db_quote;
  DB::Utils db_utils;
  Pg pg;

  static constexpr int SLOW_QUERY_EVERY = 100;

  std::map<std::string, std::string> flags;

  std::string pub_sub_clock_key();

  void load_config();
};
} // namespace Alpaca

#endif

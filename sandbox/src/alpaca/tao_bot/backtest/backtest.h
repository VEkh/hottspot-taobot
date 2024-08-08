#ifndef ALPACA__TAO_BOT_BACKTEST_H
#define ALPACA__TAO_BOT_BACKTEST_H

#include "alpaca/types.cpp"                 // Alpaca::t
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/market_close/market_close.cpp" // DB::MarketClose
#include "db/quote/quote.cpp"               // DB::Quote
#include "db/utils/utils.cpp"               // DB::Utils
#include "lib/formatted.cpp"                // Formatted
#include "lib/pg/pg.cpp"                    // Pg
#include "types.cpp"                        // Global::t
#include <list>                             // std::list
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
  //                should therefore accompany an `..account_stop_loss_ratio`
  //                setting of `0.0`.
  struct config_t {
    double account_margin_multiplier = 0.00;
    double account_starting_equity = 0.00;
    std::string api_key;
    std::string api_key_id;
    bool clock_sync = true;
    double end_epoch = 0;
    bool force_exec_slow_queries = false;
    double start_epoch = 0;
  } config;

  struct init_args_t {
    Pg conn;
    std::list<std::string> env_symbols;
    std::map<std::string, std::string> flags;
    std::string symbol;
  };

  struct upsert_account_stat_args_t {
    double current_epoch;
    account_snapshot_t current_snapshot;
    bool debug = false;
    double end_at = 0.0;
    bool force = false;
  };

  TaoBotBacktest(){};
  TaoBotBacktest(const init_args_t);

  DB::MarketClose db_market_close;

  bool is_active = false;
  int slow_query_countdown = 0;
  long int started_at = time(nullptr);
  std::string symbol;

  bool has_reached_end(const double);
  bool should_exec_slow_query(const double);

  double next_market_open_epoch(const double, const int);

  std::string fetch_asset();
  std::string fetch_order(const order_t *, const quote_t &);

  void await_env_market_close(const double, const double);
  void place_order(const long int, order_t *);
  void upsert_account_stat(const upsert_account_stat_args_t);

private:
  DB::AccountStat db_account_stat;
  DB::Quote db_quote;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg pg;

  static constexpr int SLOW_QUERY_EVERY = 100;

  std::list<std::string> env_symbols;
  std::map<std::string, std::string> flags;

  bool should_await_env_market_close(const double, const double);

  void load_config();
};
} // namespace Alpaca

#endif

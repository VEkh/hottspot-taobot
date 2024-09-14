#ifndef BACKTEST_H
#define BACKTEST_H

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

class Backtest {
public:
  using account_snapshot_t = Global::t::account_snapshot_t;
  using market_epochs_t = Global::t::market_epochs_t;
  using quote_t = Global::t::quote_t;

  struct config_t {
    double account_margin_multiplier = 0.00;
    double account_starting_equity = 0.00;
    std::string api_key;
    std::string api_key_id;
    double end_epoch = 0;
    bool force_exec_slow_queries = false;
    double start_epoch = 0;
  } config;

  struct init_args_t {
    std::string api_client_name;
    Pg conn;
    std::list<std::string> env_symbols;
    std::map<std::string, std::string> flags;
    std::string symbol;
  };

  struct upsert_account_stat_args_t {
    double current_epoch;
    account_snapshot_t current_snapshot;
    bool debug = false;
    bool force = false;
    market_epochs_t market_epochs;
  };

  Backtest(){};
  Backtest(const init_args_t);

  DB::MarketClose db_market_close;
  bool is_active = false;
  int slow_query_countdown = 0;
  long int started_at = time(nullptr);

  bool has_reached_end(const double);
  bool should_exec_slow_query(const double);

  void await_env_market_close(const double, const double);
  void upsert_account_stat(const upsert_account_stat_args_t);

protected:
  static constexpr int SLOW_QUERY_EVERY = 100;

  DB::AccountStat db_account_stat;
  DB::Quote db_quote;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;
  std::list<std::string> env_symbols;
  std::map<std::string, std::string> flags;
  std::string config_path;
  std::string symbol;

  bool should_await_env_market_close(const double, const double);

  void load_config();
};

#endif

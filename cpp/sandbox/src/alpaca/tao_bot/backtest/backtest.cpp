#ifndef ALPACA__TAO_BOT_BACKTEST
#define ALPACA__TAO_BOT_BACKTEST

#include "backtest.h" // Alpaca::TaoBotBacktest
#include "fetch_order.cpp"
#include "has_reached_now.cpp"                  // has_reached_now
#include "lib/pg/pg.cpp"                        // Pg
#include "load_config.cpp"                      // load_config
#include "models/account_stat/account_stat.cpp" // DB::AccountStat
#include "models/utils/utils.cpp"               // DB::Utils
#include "next_day_market_open_epoch.cpp"
#include "place_order.cpp"
#include "should_exec_slow_query.cpp"
#include "upsert_account_stat.cpp"

Alpaca::TaoBotBacktest::TaoBotBacktest(
    Pg conn, std::map<std::string, std::string> flags_) {
  this->db_account_stat = DB::AccountStat(conn);
  this->db_utils = DB::Utils(conn);
  this->flags = flags_;

  load_config();
}

#endif

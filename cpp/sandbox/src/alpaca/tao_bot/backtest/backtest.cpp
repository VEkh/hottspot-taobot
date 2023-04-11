#ifndef ALPACA__TAO_BOT_BACKTEST
#define ALPACA__TAO_BOT_BACKTEST

#include "backtest.h"      // Alpaca::TaoBotBacktest
#include "lib/pg/pg.cpp"   // Pg
#include "load_config.cpp" // load_config
#include "should_exec_slow_query.cpp"
#include "upsert_account_stat.cpp"

Alpaca::TaoBotBacktest::TaoBotBacktest(
    Pg conn, std::map<std::string, std::string> flags_) {
  this->db_account_stat = DB::AccountStat(conn);
  this->flags = flags_;

  load_config();
}

#endif

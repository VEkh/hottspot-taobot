#ifndef ALPACA__TAO_BOT_BACKTEST
#define ALPACA__TAO_BOT_BACKTEST

#include "backtest.h" // Alpaca::TaoBotBacktest
#include "await_env_market_close.cpp"
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/market_close/market_close.cpp" // DB::MarketClose
#include "db/quote/quote.cpp"               // DB::Quote
#include "db/utils/utils.cpp"               // DB::Utils
#include "fetch_order.cpp"
#include "has_reached_end.cpp" // has_reached_end
#include "lib/pg/pg.cpp"       // Pg
#include "lib/utils/io.cpp"    // ::utils::io
#include "load_config.cpp"     // load_config
#include "next_market_open_epoch.cpp"
#include "place_order.cpp"
#include "should_exec_slow_query.cpp"
#include "upsert_account_stat.cpp"

Alpaca::TaoBotBacktest::TaoBotBacktest(const init_args_t args) {
  Pg conn = args.conn;

  this->pg = conn;
  this->db_account_stat = DB::AccountStat(this->pg);
  this->db_market_close = DB::MarketClose(this->pg);
  this->db_quote = DB::Quote(this->pg);
  this->db_utils = DB::Utils(this->pg);
  this->env_symbols = args.env_symbols;
  this->flags = args.flags;
  this->symbol = args.symbol;

  this->db_utils.set_param({"statement_timeout", "1000"});

  load_config();
}

#endif

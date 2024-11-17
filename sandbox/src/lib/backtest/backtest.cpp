#ifndef BACKTEST
#define BACKTEST

#include "backtest.h"                       // Backtest, init_args_t
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/market_close/market_close.cpp" // DB::MarketClose
#include "db/quote/quote.cpp"               // DB::Quote
#include "db/utils/utils.cpp"               // DB::Utils
#include "lib/pg/pg.cpp"                    // Pg
#include "lib/utils/io.cpp"                 // ::utils::io
#include "load_config.cpp"                  // load_config
#include <string>                           // std::string

#include "await_env_market_close.cpp"
#include "has_reached_end.cpp"
#include "should_exec_slow_query.cpp"
#include "upsert_account_stat.cpp"

Backtest::Backtest(const init_args_t args) {
  this->conn = args.conn;
  this->db_account_stat = DB::AccountStat(this->conn);
  this->db_market_close = DB::MarketClose(this->conn);
  this->db_quote = DB::Quote(this->conn);
  this->db_utils = DB::Utils(this->conn);
  this->env_symbols = args.env_symbols;
  this->flags = args.flags;
  this->symbol = args.symbol;

  this->db_utils.set_param({"statement_timeout", "10000"});

  this->config_path = std::string(APP_DIR) + "/config/" + args.api_client_name +
                      "/credentials.json";

  load_config();
}

#endif

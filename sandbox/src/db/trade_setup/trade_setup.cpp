#ifndef DB__TRADE_SETUP
#define DB__TRADE_SETUP

#include "trade_setup.h"      // DB::TradeSetup
#include "db/utils/utils.cpp" // DB::Utils

#include "find_or_create_by.cpp"

DB::TradeSetup::TradeSetup(Pg c) {
  this->conn = c;
  this->db_utils = DB::Utils(this->conn);

  this->db_utils.set_param({"statement_timeout", "10000"});
}

#endif

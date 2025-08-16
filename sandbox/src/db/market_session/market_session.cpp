#ifndef DB__MARKET_SESSION
#define DB__MARKET_SESSION

#include "market_session.h"   // DB::MarketSession
#include "db/utils/utils.cpp" // DB::Utils

#include "find_or_create_by.cpp"

DB::MarketSession::MarketSession(Pg c) {
  this->conn = c;
  this->db_utils = DB::Utils(this->conn);

  this->db_utils.set_param({"statement_timeout", "10000"});
}

#endif

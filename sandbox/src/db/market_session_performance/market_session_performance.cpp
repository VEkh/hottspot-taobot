#ifndef DB__MARKET_SESSION_PERFORMANCE
#define DB__MARKET_SESSION_PERFORMANCE

#include "market_session_performance.h" // DB::MarketSessionPerformance
#include "db/utils/utils.cpp"           // DB::Utils

#include "upsert.cpp"

DB::MarketSessionPerformance::MarketSessionPerformance(Pg c) {
  this->conn = c;
  this->db_utils = DB::Utils(this->conn);

  this->db_utils.set_param({"statement_timeout", "10000"});
}

#endif
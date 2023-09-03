#ifndef PERFORMANCE__LOGGER
#define PERFORMANCE__LOGGER

#include "logger.h"
#include "lib/pg/pg.cpp" // Pg
#include "log_daily_snapshots.cpp"

Performance::Logger::Logger(Pg c) {
  this->conn = c;
  this->db_account_stat = DB::AccountStat(this->conn);
}

#endif

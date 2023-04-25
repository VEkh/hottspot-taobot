#ifndef ALPACA__PERFORMANCE_LOGGER
#define ALPACA__PERFORMANCE_LOGGER

#include "performance_logger.h"
#include "lib/pg/pg.cpp" // Pg
#include "log_benchmark.cpp"
#include "log_daily_snapshots.cpp"

Alpaca::PerformanceLogger::PerformanceLogger(Pg c) {
  this->conn = c;
  this->db_account_stat = DB::AccountStat(this->conn);
}

#endif

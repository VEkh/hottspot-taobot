#ifndef ALPACA__PERFORMANCE_LOGGER_H
#define ALPACA__PERFORMANCE_LOGGER_H

#include "lib/pg/pg.cpp"                        // Pg
#include "models/account_stat/account_stat.cpp" // DB::AccountStat
#include "types.cpp"                            // Global::t
#include <string>                               // std::string

namespace Alpaca {
class PerformanceLogger {
public:
  PerformanceLogger(Pg c);

  void log_daily_snapshots(const std::string);

private:
  using account_snapshot_t = Global::t::account_snapshot_t;

  DB::AccountStat db_account_stat;
  Pg conn;
};
} // namespace Alpaca

#endif

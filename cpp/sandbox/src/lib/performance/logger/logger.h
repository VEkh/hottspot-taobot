#ifndef PERFORMANCE__LOGGER_H
#define PERFORMANCE__LOGGER_H

#include "db/account_stat/account_stat.h" // DB::AccountStat
#include "lib/pg/pg.h"                    // Pg
#include "types.cpp"                      // Global::t
#include <string>                         // std::string

namespace Performance {
class Logger {
public:
  Logger(){};
  Logger(Pg c);

  void log_daily_snapshots(const std::string);

private:
  using account_snapshot_t = Global::t::account_snapshot_t;

  DB::AccountStat db_account_stat;
  Pg conn;
};
} // namespace Performance

#endif
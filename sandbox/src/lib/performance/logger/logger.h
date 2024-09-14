#ifndef PERFORMANCE__LOGGER_H
#define PERFORMANCE__LOGGER_H

#include "db/account_stat/account_stat.h" // DB::AccountStat
#include "lib/pg/pg.cpp"                  // Pg
#include "types.cpp"                      // Global::t
#include <map>                            // std::map
#include <string>                         // std::string
#include <time.h>                         // time

namespace Performance {
class Logger {
public:
  struct init_args_t {
    std::string api_key;
    std::string api_name;
    Pg conn;
    bool debug = false;
    std::string end_at;
    std::string start_at;
  };

  Logger(){};
  Logger(const init_args_t);

  void log_daily_snapshots();

private:
  using account_snapshot_t = Global::t::account_snapshot_t;

  DB::AccountStat db_account_stat;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;
  bool debug;
  std::string api_key;
  std::string api_name;
  std::string end_at;
  std::string start_at;

  const double timer_start = time(nullptr);

  void validate();
}; // namespace Performance
} // namespace Performance

#endif

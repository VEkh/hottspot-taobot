#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_H
#define PERFORMANCE__ACCOUNT_SNAPSHOT_H

#include "db/account_stat/account_stat.h" // DB::AccountStat
#include "lib/pg/pg.cpp"                  // Pg
#include "types.cpp"                      // Global::t
#include <list>                           // std::list
#include <string>                         // std::string
#include <time.h>                         // time

namespace Performance {
class AccountSnapshot {
public:
  struct init_args_t {
    std::string api_key;
    std::string api_name;
    Pg conn;
    bool debug = false;
    std::string end_at;
    std::string start_at;
  };

  AccountSnapshot(){};
  AccountSnapshot(const init_args_t);

  void daily();

private:
  using account_snapshot_t = Global::t::account_snapshot_t;

  struct config_t {
    std::string api_key;
    std::string api_key_id;
    std::string api_name;
    bool debug;
    std::string end_at;
    std::string start_at;
  };

  struct stats_t {
    double daily_net_pl_ratio = 0.0;
    int day_count = 0;
    int loss_count = 0;
    double net_pl = 0.0;
    account_snapshot_t original_snapshot;
    int win_count = 0;
  };

  DB::AccountStat db_account_stat;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;
  config_t config;
  stats_t stats;

  const double timer_start = time(nullptr);

  void build_stats(std::list<account_snapshot_t> &);
  void load_env();
  void log_duration();
  void log_stats();
  void validate();
}; // namespace Performance
} // namespace Performance

#endif

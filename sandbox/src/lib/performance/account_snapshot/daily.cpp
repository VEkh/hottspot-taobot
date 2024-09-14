#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_daily
#define PERFORMANCE__ACCOUNT_SNAPSHOT_daily

#include "account_snapshot.h" // Performance::AccountSnapshot, account_snapshot_t
#include "build_stats.cpp"    // build_stats
#include "log_duration.cpp"   // log_duration
#include "log_stats.cpp"      // log_stats
#include <list>               // std::list

void Performance::AccountSnapshot::daily() {
  std::list<account_snapshot_t> snapshots =
      this->db_account_stat.get_daily_snapshots({
          .api_key_id = this->config.api_key_id,
          .debug = this->config.debug,
          .end_at = this->config.end_at,
          .start_at = this->config.start_at,
      });

  build_stats(snapshots);
  log_stats();
  log_duration();
}

#endif

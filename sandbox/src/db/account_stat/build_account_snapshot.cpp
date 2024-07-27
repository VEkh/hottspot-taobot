#ifndef DB__ACCOUNT_STAT_build_account_snapshot
#define DB__ACCOUNT_STAT_build_account_snapshot

#include "account_stat.h" // DB::AccountStat, account_stat_t
#include <algorithm>      // std::max, std::min
#include <list>           // std::list
#include <math.h>         // INFINITY

DB::AccountStat::account_snapshot_t DB::AccountStat::build_account_snapshot(
    const std::list<account_stat_t> &account_stats) {
  account_snapshot_t snapshot = {
      .max_equity = -INFINITY,
      .min_equity = INFINITY,
      .original_equity = 0.0,
      .original_margin_buying_power = 0.0,
  };

  for (const account_stat_t account_stat : account_stats) {
    snapshot.api_key_id = account_stat.api_key_id;
    snapshot.equity = account_stat.equity;
    snapshot.margin_buying_power = account_stat.margin_buying_power;
    snapshot.margin_multiplier = account_stat.margin_multiplier;
    snapshot.timestamp = account_stat.inserted_at;

    snapshot.original_equity = snapshot.original_equity
                                   ? snapshot.original_equity
                                   : account_stat.equity;

    snapshot.original_margin_buying_power =
        snapshot.original_margin_buying_power
            ? snapshot.original_margin_buying_power
            : account_stat.margin_buying_power;

    snapshot.max_equity = std::max(snapshot.max_equity, account_stat.equity);
    snapshot.min_equity = std::min(snapshot.min_equity, account_stat.equity);

    if (snapshot.max_equity == account_stat.equity) {
      snapshot.max_equity_timestamp = account_stat.inserted_at;
    }

    if (snapshot.min_equity == account_stat.equity) {
      snapshot.min_equity_timestamp = account_stat.inserted_at;
    }
  }

  return snapshot;
}

#endif

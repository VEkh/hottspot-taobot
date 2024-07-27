#ifndef DB__ACCOUNT_STAT_get_snapshot
#define DB__ACCOUNT_STAT_get_snapshot

#include "account_stat.h" // DB::AccountStat, account_stat_t, query_result_t
#include "build_account_snapshot.cpp"     // build_account_snapshot
#include "get_snapshot_account_stats.cpp" // get_snapshot_account_stats
#include "lib/formatted.cpp"              // Formatted
#include <iostream>                       // std::cout, std::endl
#include <list>                           // std::list
#include <string>                         // std::string
#include <unistd.h>                       // usleep

DB::AccountStat::account_snapshot_t
DB::AccountStat::get_snapshot(const get_snapshot_args_t args) {
  const std::list<account_stat_t> account_stats =
      get_snapshot_account_stats(args);

  if (account_stats.empty()) {
    const std::string error_message = Formatted::error_message(
        std::string("DB__ACCOUNT_STAT_get_snapshot: No account stats for ") +
        args.api_key_id);

    std::cout << error_message << std::endl;

    usleep(5e5);

    return get_snapshot(args);
  }

  return build_account_snapshot(account_stats);
}

#endif

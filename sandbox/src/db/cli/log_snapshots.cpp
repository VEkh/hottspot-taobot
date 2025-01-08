#ifndef DB__CLI_log_snapshots
#define DB__CLI_log_snapshots

#include "cli.h"                                                 // DB::Cli
#include "lib/performance/account_snapshot/account_snapshot.cpp" // Performance::AccountSnapshot
#include "lib/pg/pg.cpp"                                         // Pg
#include "lib/utils/io.cpp"                                      // ::utils::io

void DB::Cli::log_snapshots() {
  Pg pg(this->flags);
  pg.connect();

  Performance::AccountSnapshot account_snapshot({
      .api_key = this->flags["api-key"],
      .api_name = this->flags["api"],
      .conn = pg,
      .debug = ::utils::io::flag_to_bool("debug", this->flags["debug"]),
      .end_at = this->flags["end-at"],
      .start_at = this->flags["start-at"],
  });

  account_snapshot.daily();

  pg.disconnect();
}

#endif

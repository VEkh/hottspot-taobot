#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT
#define PERFORMANCE__ACCOUNT_SNAPSHOT

#include "account_snapshot.h"
#include "daily.cpp"

#include "load_env.cpp" // load_env
#include "validate.cpp" // validate
#include <locale.h>     // std::locale

Performance::AccountSnapshot::AccountSnapshot(const init_args_t args) {
  std::locale::global(std::locale("en_US.UTF-8"));

  this->config = {
      .api_key = args.api_key,
      .api_name = args.api_name,
      .debug = args.debug,
      .end_at = args.end_at,
      .start_at = args.start_at,
  };

  this->conn = args.conn;

  validate();

  this->db_account_stat = DB::AccountStat(this->conn);

  load_env();
}

#endif

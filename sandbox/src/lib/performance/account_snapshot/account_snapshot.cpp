#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT
#define PERFORMANCE__ACCOUNT_SNAPSHOT

#include "account_snapshot.h"
#include "log_daily.cpp"

#include "validate.cpp" // validate
#include <locale.h>     // std::locale

Performance::AccountSnapshot::AccountSnapshot(const init_args_t args) {
  std::locale::global(std::locale("en_US.UTF-8"));

  this->api_key = args.api_key;
  this->api_name = args.api_name;
  this->conn = args.conn;
  this->debug = args.debug;
  this->end_at = args.end_at;
  this->start_at = args.start_at;

  validate();

  this->db_account_stat = DB::AccountStat(this->conn);
}

#endif

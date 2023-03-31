#ifndef DB__ACCOUNT_STAT_H
#define DB__ACCOUNT_STAT_H

#include "lib/pg/pg.cpp" // Pg
#include "types.cpp"     // Global::t
#include <string>        // std::string

namespace DB {
class AccountStat {
public:
  using account_snapshot_t = Global::t::account_snapshot_t;

  struct get_snapshot_args_t {
    std::string api_key_id;
    double session_started_at;
    double starting_from;
    bool debug = false;
  };

  struct insert_args_t {
    std::string api_key_id;
    double equity = 0.00;
    double margin_buying_power = 0.00;
    double margin_multiplier = 0.00;
  };

  AccountStat(){};
  AccountStat(Pg c) : conn(c){};

  account_snapshot_t get_snapshot(const get_snapshot_args_t);
  void insert(const insert_args_t);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;

  account_snapshot_t result_to_account_snapshot(const query_result_t &);
};
} // namespace DB

#endif

#ifndef DB__ACCOUNT_STAT_H
#define DB__ACCOUNT_STAT_H

#include "lib/pg/pg.cpp" // Pg
#include "types.cpp"     // Global::t
#include <list>          // std::list
#include <string>        // std::string

namespace DB {
class AccountStat {
public:
  using account_snapshot_t = Global::t::account_snapshot_t;

  struct get_snapshot_args_t {
    std::string api_key_id;
    double starting_from;
    bool debug = false;
  };

  struct get_snapshot_with_computed_equity_args_t {
    std::string api_key_id;
    double starting_from;
    bool debug = false;
  };

  struct upsert_args_t {
    std::string api_key_id;
    double equity = 0.00;
    double inserted_at = 0.00;
    double margin_buying_power = 0.00;
    double margin_multiplier = 0.00;
    bool debug = false;
  };

  AccountStat(){};
  AccountStat(Pg c) : conn(c){};

  std::list<account_snapshot_t> get_daily_snapshots(const std::string,
                                                    const bool);
  account_snapshot_t get_snapshot(const get_snapshot_args_t);
  account_snapshot_t get_snapshot_with_computed_equity(
      const get_snapshot_with_computed_equity_args_t);

  void upsert(const upsert_args_t);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;

  std::list<account_snapshot_t>
  result_to_account_snapshots(const query_result_t &);
};
} // namespace DB

#endif

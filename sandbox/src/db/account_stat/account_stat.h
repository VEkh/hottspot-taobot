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

  struct account_stat_t {
    std::string api_key_id;
    double equity;
    double inserted_at;
    double margin_buying_power;
    double margin_multiplier;
  };

  struct get_daily_snapshots_args_t {
    std::string api_key_id;
    bool debug = false;
    std::string end_at;
    std::string start_at;
  };

  struct get_snapshot_args_t {
    std::string api_key_id;
    bool debug = false;
    double start_at;
  };

  struct get_snapshot_with_computed_equity_args_t {
    std::string api_key_id;
    account_snapshot_t current_snapshot;
    bool debug = false;
    double end_at;
    double start_at;
  };

  struct upsert_args_t {
    std::string api_key_id;
    bool debug = false;
    double equity = 0.00;
    double inserted_at = 0.00;
    double margin_buying_power = 0.00;
    double margin_multiplier = 0.00;
  };

  AccountStat(){};
  AccountStat(Pg c) : conn(c){};

  std::list<account_snapshot_t>
  get_daily_snapshots(const get_daily_snapshots_args_t);
  account_snapshot_t get_snapshot(const get_snapshot_args_t);
  account_snapshot_t get_snapshot_with_computed_equity(
      const get_snapshot_with_computed_equity_args_t);

  void upsert(const upsert_args_t);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;

  account_snapshot_t build_account_snapshot(const std::list<account_stat_t> &);

  std::list<account_stat_t>
  get_snapshot_account_stats(const get_snapshot_args_t);

  std::list<account_snapshot_t>
  result_to_account_snapshots(const query_result_t &);

  std::list<account_stat_t> result_to_account_stats(const query_result_t &);

  std::list<double> result_to_computed_profits(const query_result_t &);
};
} // namespace DB

#endif

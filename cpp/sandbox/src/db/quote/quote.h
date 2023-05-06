#ifndef DB__QUOTE_H
#define DB__QUOTE_H

#include "db/utils/utils.h" // DB::Utils
#include "lib/pg/pg.h"      // Pg
#include "types.cpp"        // Global::t
#include <list>             // std::list
#include <string>           // std::string
#include <vector>           // std::vector

namespace DB {
class Quote {
public:
  using one_sec_variance_avgs_t = Global::t::one_sec_variance_avgs_t;
  using quote_t = Global::t::quote_t;

  struct get_last_args_t {
    int limit = 1;
    std::string symbol;
    double timestamp_upper_bound;
    bool debug = false;
  };

  struct get_one_sec_variance_avgs_args_t {
    std::string symbol;
    double timestamp_upper_bound;
    bool debug = false;
  };

  Quote(){};
  Quote(Pg c);

  one_sec_variance_avgs_t
  get_one_sec_variance_avgs(const get_one_sec_variance_avgs_args_t);

  std::vector<quote_t> get(const std::string, const double);
  std::vector<quote_t> get_last(const get_last_args_t);

  void upsert(const quote_t);
  void upsert(const std::vector<quote_t>);
  void watch_avg_one_sec_variances(const std::list<std::string> &);

private:
  using query_result_t = Pg::query_result_t;

  DB::Utils db_utils;
  Pg conn;

  double result_to_stop_profit(const query_result_t &);

  one_sec_variance_avgs_t
  result_to_one_sec_variance_avgs(const query_result_t &);

  std::vector<quote_t> result_to_quotes(const query_result_t &);
  void insert_latest_avg_one_sec_variances(const std::list<std::string> &);
};
} // namespace DB

#endif

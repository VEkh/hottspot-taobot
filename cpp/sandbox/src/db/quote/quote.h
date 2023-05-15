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
  using avg_one_sec_variances_t = Global::t::avg_one_sec_variances_t;
  using quote_t = Global::t::quote_t;

  struct get_last_args_t {
    int limit = 1;
    std::string symbol;
    double timestamp_upper_bound;
    bool debug = false;
  };

  struct get_avg_one_sec_variances_args_t {
    std::string symbol;
    double timestamp_upper_bound;
    bool debug = false;
  };

  struct insert_avg_one_sec_variance_args_t {
    long int id = 0;
    std::string symbol;
    bool debug = true;
  };

  Quote(){};
  Quote(Pg c);

  avg_one_sec_variances_t
  get_avg_one_sec_variances(const get_avg_one_sec_variances_args_t);

  std::vector<quote_t> get(const std::string, const double);
  std::vector<quote_t> get_last(const get_last_args_t);

  void insert_avg_one_sec_variance(const insert_avg_one_sec_variance_args_t);
  void upsert(const quote_t);
  void upsert(const std::vector<quote_t>);
  void watch_avg_one_sec_variances(const std::list<std::string> &);

private:
  using query_result_t = Pg::query_result_t;

  DB::Utils db_utils;
  Pg conn;

  double result_to_stop_profit(const query_result_t &);

  avg_one_sec_variances_t
  result_to_avg_one_sec_variances(const query_result_t &);

  std::vector<quote_t> result_to_quotes(const query_result_t &);
  void insert_latest_avg_one_sec_variances(const std::list<std::string> &);
};
} // namespace DB

#endif

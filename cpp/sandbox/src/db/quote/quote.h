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
  using query_result_t = Pg::query_result_t;
  using quote_t = Global::t::quote_t;

  struct get_last_args_t {
    int limit = 1;
    long int limit_offset = 0;
    std::string symbol;
    double timestamp_upper_bound;
    bool debug = false;
  };

  struct get_avg_one_sec_variances_args_t {
    std::string symbol;
    double timestamp_upper_bound;
    bool debug = false;
  };

  struct upsert_avg_one_sec_variance_args_t {
    long int id = 0;
    std::string symbol;
    bool debug = true;
  };

  struct upsert_all_avg_one_sec_variances_args_t {
    std::string starting_from;
    std::string symbol;
    bool debug = false;
  };

  Quote(){};
  Quote(Pg c);

  avg_one_sec_variances_t
  get_avg_one_sec_variances(const get_avg_one_sec_variances_args_t);

  std::vector<quote_t> get(const std::string, const double);
  std::vector<quote_t> get_last(const get_last_args_t);
  std::vector<quote_t> result_to_quotes(const query_result_t &);

  void upsert(const quote_t);
  void upsert(const std::vector<quote_t>);
  void upsert_all_avg_one_sec_variances(
      const upsert_all_avg_one_sec_variances_args_t);
  void upsert_avg_one_sec_variance(const upsert_avg_one_sec_variance_args_t);

private:
  DB::Utils db_utils;
  Pg conn;

  double result_to_stop_profit(const query_result_t &);

  avg_one_sec_variances_t
  result_to_avg_one_sec_variances(const query_result_t &);
};
} // namespace DB

#endif

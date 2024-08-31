#ifndef DB__QUOTE_H
#define DB__QUOTE_H

#include "db/utils/utils.h"  // DB::Utils
#include "lib/formatted.cpp" // Formatted
#include "lib/pg/pg.h"       // Pg
#include "types.cpp"         // Global::t
#include <list>              // std::list
#include <string>            // std::string

namespace DB {
class Quote {
public:
  using query_result_t = Pg::query_result_t;
  using quote_t = Global::t::quote_t;

  struct avg_one_sec_variances_t {
    double latest = 0.00;
    double running = 0.00;
  };

  struct get_last_args_t {
    bool debug = false;
    double end_at;
    int limit = 0;
    long int limit_offset = 0;
    std::string sort_direction = "desc";
    double start_at = 0.0;
    std::string symbol;
  };

  struct get_avg_one_sec_variances_args_t {
    bool debug = false;
    std::string symbol;
    double end_at;
  };

  struct upsert_avg_one_sec_variance_args_t {
    bool debug = true;
    long int id = 0;
    std::string symbol;
  };

  struct upsert_all_avg_one_sec_variances_args_t {
    bool debug = false;
    std::string end_at;
    std::string start_at;
    std::string symbol;
  };

  Quote(){};
  Quote(Pg c);

  avg_one_sec_variances_t
  get_avg_one_sec_variances(const get_avg_one_sec_variances_args_t);

  std::list<quote_t> get(const std::string, const double);
  std::list<quote_t> get_last(const get_last_args_t);
  std::list<quote_t> result_to_quotes(const query_result_t &);

  void upsert(const quote_t);
  void upsert(const std::list<quote_t>);
  void upsert_all_avg_one_sec_variances(
      const upsert_all_avg_one_sec_variances_args_t);
  void upsert_avg_one_sec_variance(const upsert_avg_one_sec_variance_args_t);

private:
  using candle_t = Global::t::candle_t;

  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;

  double result_to_stop_profit(const query_result_t &);

  avg_one_sec_variances_t
  result_to_avg_one_sec_variances(const query_result_t &);
};
} // namespace DB

#endif

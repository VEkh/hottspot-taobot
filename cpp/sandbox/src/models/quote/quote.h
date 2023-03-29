#ifndef DB__QUOTE_H
#define DB__QUOTE_H

#include "lib/pg/pg.cpp" // Pg
#include "types.cpp"     // Global::t
#include <string>        // std::string
#include <vector>        // std::vector

namespace DB {
class Quote {
public:
  using one_sec_variance_avgs_t = Global::t::one_sec_variance_avgs_t;
  using quote_t = Global::t::quote_t;

  struct get_last_args_t {
    bool debug = false;
    int limit = 1;
    std::string symbol;
  };

  Quote(){};
  Quote(Pg &c) : conn(c){};

  one_sec_variance_avgs_t get_one_sec_variance_avgs(const std::string,
                                                    const bool);

  std::vector<quote_t> get(const std::string, const double);
  std::vector<quote_t> get_last(get_last_args_t);

  void insert_latest_avg_one_sec_variances();
  void upsert(const quote_t);
  void upsert(const std::vector<quote_t>);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;

  one_sec_variance_avgs_t
  result_to_one_sec_variance_avgs(const query_result_t &);

  std::vector<quote_t> result_to_quotes(const query_result_t &);
};
} // namespace DB

#endif

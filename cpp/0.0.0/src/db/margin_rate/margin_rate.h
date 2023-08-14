#ifndef DB__MARGIN_RATE_H
#define DB__MARGIN_RATE_H

#include "lib/pg/pg.h" // Pg
#include <string>      // std::string

namespace DB {
class MarginRate {
public:
  struct margin_rate_t {
    double multiplier;
    std::string symbol;
  };

  struct insert_args_t {
    double multiplier;
    std::string symbol;
    bool debug = false;
  };

  MarginRate() {}
  MarginRate(Pg c) : conn(c) {}

  margin_rate_t get(const std::string, const bool);
  void insert(const insert_args_t);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;

  margin_rate_t result_to_margin_rate(const query_result_t &);
};
} // namespace DB

#endif

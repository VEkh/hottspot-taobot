#ifndef DB__QUOTE_H
#define DB__QUOTE_H

#include "lib/pg/pg.cpp" // Pg
#include "types.cpp"     // Global::t
#include <string>        // std::string
#include <vector>        // std::vector

namespace DB {
class Quote {
public:
  using quote_t = Global::t::quote_t;

  Quote(Pg &c) : conn(c){};

  std::vector<quote_t> get(const std::string, const double);

  void upsert(std::vector<quote_t>);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;

  std::vector<quote_t> result_to_collection(const query_result_t &);
};
} // namespace DB

#endif

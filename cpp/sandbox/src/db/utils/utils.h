#ifndef DB__UTILS_H
#define DB__UTILS_H

#include "lib/pg/pg.cpp" // Pg
#include <string>        // std::string
#include <utility>       // std::pair

namespace DB {
class Utils {
public:
  using query_result_t = Pg::query_result_t;

  Utils(){};
  Utils(Pg c) : conn(c) {}

  std::string generate_uuid(const bool);
  void set_param(const std::pair<std::string, std::string>, const bool);

private:
  Pg conn;

  std::string result_to_uuid(const query_result_t &);
};
} // namespace DB

#endif

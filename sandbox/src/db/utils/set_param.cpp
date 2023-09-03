#ifndef DB__UTILS_set_param
#define DB__UTILS_set_param

#include "utils.h"    // DB::Utils
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string
#include <utility>    // std::pair

void DB::Utils::set_param(const std::pair<std::string, std::string> param,
                          const bool debug = false) {
  const char *query_format = "set %s = %s";
  const std::string key = param.first;
  const std::string value = param.second;

  char *sanitized_value =
      PQescapeLiteral(this->conn.conn, value.c_str(), value.size());

  const size_t query_l =
      strlen(query_format) + key.size() + strlen(sanitized_value);

  char query[query_l];

  snprintf(query, query_l, query_format, key.c_str(), sanitized_value);

  PQfreemem(sanitized_value);

  this->conn.exec(query, debug);
}

#endif

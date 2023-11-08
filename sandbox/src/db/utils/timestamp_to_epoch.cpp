#ifndef DB__UTILS_timestamp_to_epoch
#define DB__UTILS_timestamp_to_epoch

#include "utils.h"    // DB::Utils, query_result_t
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::stod, std::string

double DB::Utils::timestamp_to_epoch(const std::string timestamp,
                                     const char *time_zone = "UTC",
                                     const bool debug = false) {
  const char *query_format = R"(
    select
      extract(epoch from %s::timestamp at time zone %s)
  )";

  char *sanitized_timestamp =
      PQescapeLiteral(this->conn.conn, timestamp.c_str(), timestamp.size());

  char *sanitized_time_zone =
      PQescapeLiteral(this->conn.conn, time_zone, strlen(time_zone));

  const size_t query_l = strlen(query_format) + strlen(sanitized_timestamp) +
                         strlen(sanitized_time_zone);

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_timestamp,
           sanitized_time_zone);

  PQfreemem(sanitized_timestamp);
  PQfreemem(sanitized_time_zone);

  const query_result_t result = this->conn.exec(query, debug);

  if (!result.tuples.empty()) {
    return std::stod(result.tuples.front());
  }

  return 0;
}

#endif

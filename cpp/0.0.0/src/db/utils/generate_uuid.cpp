#ifndef DB__UTILS_generate_uuid
#define DB__UTILS_generate_uuid

#include "result_to_uuid.cpp" // result_to_uuid
#include "utils.h"            // DB::Utils, query_result_t
#include <string>             // std::string

std::string DB::Utils::generate_uuid(const bool debug = false) {
  const char *query = "select gen_random_uuid() as uuid";

  query_result_t result = this->conn.exec(query, debug);
  return result_to_uuid(result);
}

#endif

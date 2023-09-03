#ifndef DB__UTILS_result_to_uuid
#define DB__UTILS_result_to_uuid

#include "lib/utils/string.cpp" // ::utils::string
#include "utils.h"              // DB::Utils, query_result_t
#include <string>               // std::string

std::string DB::Utils::result_to_uuid(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::string out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "uuid") {
        out = value;
      }
    }
  }

  return out;
}

#endif

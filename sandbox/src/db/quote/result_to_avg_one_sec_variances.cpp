#ifndef DB__QUOTE_result_to_avg_one_sec_variances
#define DB__QUOTE_result_to_avg_one_sec_variances

#include "lib/utils/string.cpp" // ::utils::string
#include "quote.h" // DB::Quote, avg_one_sec_variances_t, query_result_t
#include <string>  // std::stod, std::string
#include <vector>  // std::vector

DB::Quote::avg_one_sec_variances_t
DB::Quote::result_to_avg_one_sec_variances(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  avg_one_sec_variances_t out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "latest") {
        out.latest = std::stod(value);
      }

      if (field == "running") {
        out.running = std::stod(value);
      }
    }
  }

  return out;
}

#endif

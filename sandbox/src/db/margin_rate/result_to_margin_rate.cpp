#ifndef DB__MARGIN_RATE_result_to_margin_rate
#define DB__MARGIN_RATE_result_to_margin_rate

#include "lib/utils/string.cpp" // ::utils::string
#include "margin_rate.h"        // DB::MarginRate, margin_rate_t, query_result_t
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

DB::MarginRate::margin_rate_t
DB::MarginRate::result_to_margin_rate(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  margin_rate_t record;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "multiplier") {
        record.multiplier = std::stod(value);
      }

      if (field == "symbol") {
        record.symbol = value;
      }
    }
  }

  return record;
}

#endif

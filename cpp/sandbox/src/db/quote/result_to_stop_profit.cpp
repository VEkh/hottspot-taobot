#ifndef DB__QUOTE_result_to_stop_profit
#define DB__QUOTE_result_to_stop_profit

#include "lib/utils/string.cpp" // ::utils::string
#include "quote.h"              // DB::Quote, query_result_t
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

double DB::Quote::result_to_stop_profit(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  double out = 0.00;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "stop_profit") {
        out = std::stod(value);
      }
    }
  }

  return out;
}

#endif

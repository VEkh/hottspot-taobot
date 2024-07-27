#ifndef DB__ACCOUNT_STAT_result_to_computed_profits
#define DB__ACCOUNT_STAT_result_to_computed_profits

#include "account_stat.h"       // DB::AccountStat, query_result_t
#include "lib/utils/string.cpp" // ::utils::string
#include <list>                 // std::list
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

std::list<double>
DB::AccountStat::result_to_computed_profits(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::list<double> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    double record = 0.0;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "profit") {
        record = std::stod(value);
      }
    }

    out.push_back(record);
  }

  return out;
}

#endif

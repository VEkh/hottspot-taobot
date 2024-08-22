#ifndef DB__PRICE_ACTION_result_to_stats
#define DB__PRICE_ACTION_result_to_stats

#include "lib/utils/string.cpp" // ::utils::string
#include "price_action.h" // DB::PriceAction, price_action_stats_t, query_result_t
#include <string>         // std::stod, std::string
#include <vector>         // std::vector

DB::PriceAction::price_action_stats_t
DB::PriceAction::result_to_stats(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  price_action_stats_t out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "avg") {
        out.avg = std::stod(value);
      }

      if (field == "std") {
        out.std = std::stod(value);
      }
    }
  }

  return out;
}

#endif

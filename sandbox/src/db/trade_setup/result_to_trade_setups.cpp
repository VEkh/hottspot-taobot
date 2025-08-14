#ifndef DB__TRADE_SETUP_result_to_trade_setups
#define DB__TRADE_SETUP_result_to_trade_setups

#include "lib/utils/string.cpp" // ::utils::string
#include "trade_setup.h"        // DB::TradeSetup, query_result_t, trade_setup_t
#include <list>                 // std::list
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

std::list<DB::TradeSetup::trade_setup_t>
DB::TradeSetup::result_to_trade_setups(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::list<trade_setup_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    trade_setup_t trade_setup;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "id") {
        trade_setup.id = std::stoi(value);
      }

      if (field == "priority") {
        trade_setup.priority = std::stoi(value);
      }

      if (field == "reverse_percentile_id") {
        trade_setup.reverse_percentile_id = std::stoi(value);
      }

      if (field == "stop_profit_id") {
        trade_setup.stop_profit_id = std::stoi(value);
      }
    }

    out.push_back(trade_setup);
  }

  return out;
}

#endif

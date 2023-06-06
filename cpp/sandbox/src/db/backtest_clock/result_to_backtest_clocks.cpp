#ifndef DB__BACKTEST_CLOCK_result_to_backtest_clocks
#define DB__BACKTEST_CLOCK_result_to_backtest_clocks

#include "backtest_clock.h" // DB::BacktestClock, backtest_clock_t, query_result_t
#include "lib/utils/string.cpp" // ::utils::string
#include <list>                 // std::list
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

std::list<DB::BacktestClock::backtest_clock_t>
DB::BacktestClock::result_to_backtest_clocks(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;

  std::list<backtest_clock_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");

    backtest_clock_t record;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "api_key_id") {
        record.api_key_id = value;
      }

      if (field == "set_to") {
        record.set_to = std::stod(value);
      }

      if (field == "symbol") {
        record.symbol = value;
      }
    }

    out.push_back(record);
  }

  return out;
}

#endif

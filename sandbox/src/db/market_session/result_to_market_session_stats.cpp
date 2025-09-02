#ifndef DB__MARKET_SESSION_result_to_market_session_stats
#define DB__MARKET_SESSION_result_to_market_session_stats

#include "lib/utils/string.cpp" // ::utils::string
#include "market_session.h" // DB::MarketSession, query_result_t, market_session_stats_t
#include <string>           // std::stod, std::string
#include <vector>           // std::vector

DB::MarketSession::market_session_stats_t
DB::MarketSession::result_to_market_session_stats(
    const query_result_t &result) {
  if (result.tuples.empty()) {
    return {0.0, 0.0, 0.0, 0.0};
  }

  const std::vector<std::string> fields = result.fields;
  const std::string row = result.tuples[0];
  const std::vector<std::string> values = ::utils::string::split(row, ",");

  market_session_stats_t stats = {0.0, 0.0, 0.0, 0.0};

  for (int i = 0; i < result.fields_n; i++) {
    const std::string field = fields.at(i);
    const std::string value = values.at(i);

    if (value.empty()) {
      continue;
    }

    if (field == "range_open_percent_median") {
      stats.range_open_percent_median = std::stod(value);
    } else if (field == "range_open_percent_std_dev") {
      stats.range_open_percent_std_dev = std::stod(value);
    } else if (field == "warm_up_range_open_percent_median") {
      stats.warm_up_range_open_percent_median = std::stod(value);
    } else if (field == "warm_up_range_open_percent_std_dev") {
      stats.warm_up_range_open_percent_std_dev = std::stod(value);
    }
  }

  return stats;
}

#endif

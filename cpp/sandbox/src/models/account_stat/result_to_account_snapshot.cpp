#ifndef DB__ACCOUNT_STAT_result_to_account_snapshot
#define DB__ACCOUNT_STAT_result_to_account_snapshot

#include "account_stat.h" // DB::AccountStat, account_snapshot_t, query_result_t
#include "lib/utils/string.cpp" // ::utils::string
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

DB::AccountStat::account_snapshot_t
DB::AccountStat::result_to_account_snapshot(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  account_snapshot_t out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "api_key_id") {
        out.api_key_id = value;
      }

      if (field == "equity") {
        out.equity = std::stod(value);
      }

      if (field == "margin_buying_power") {
        out.margin_buying_power = std::stod(value);
      }

      if (field == "margin_multiplier") {
        out.margin_multiplier = std::stod(value);
      }

      if (field == "max_equity") {
        out.max_equity = std::stod(value);
      }

      if (field == "max_equity_timestamp") {
        out.max_equity_timestamp = std::stod(value);
      }

      if (field == "min_equity") {
        out.min_equity = std::stod(value);
      }

      if (field == "min_equity_timestamp") {
        out.min_equity_timestamp = std::stod(value);
      }

      if (field == "original_equity") {
        out.original_equity = std::stod(value);
      }

      if (field == "original_margin_buying_power") {
        out.original_margin_buying_power = std::stod(value);
      }

      if (field == "session_max_equity") {
        out.session_max_equity = std::stod(value);
      }

      if (field == "session_max_equity_timestamp") {
        out.session_max_equity_timestamp = std::stod(value);
      }

      if (field == "session_original_equity") {
        out.session_original_equity = std::stod(value);
      }

      if (field == "timestamp" || field == "timestamp_epoch") {
        out.timestamp = std::stod(value);
      }
    }
  }

  return out;
}

#endif

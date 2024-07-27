#ifndef DB__ACCOUNT_STAT_result_to_account_stats
#define DB__ACCOUNT_STAT_result_to_account_stats

#include "account_stat.h" // DB::AccountStat, account_stat_t, query_result_t
#include "lib/utils/string.cpp" // ::utils::string
#include <list>                 // std::list
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

std::list<DB::AccountStat::account_stat_t>
DB::AccountStat::result_to_account_stats(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::list<account_stat_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    account_stat_t record;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "api_key_id") {
        record.api_key_id = value;
      }

      if (field == "equity") {
        record.equity = std::stod(value);
      }

      if (field == "inserted_at" || field == "inserted_at_epoch") {
        record.inserted_at = std::stod(value);
      }

      if (field == "margin_buying_power") {
        record.margin_buying_power = std::stod(value);
      }

      if (field == "margin_multiplier") {
        record.margin_multiplier = std::stod(value);
      }
    }

    out.push_back(record);
  }

  return out;
}

#endif

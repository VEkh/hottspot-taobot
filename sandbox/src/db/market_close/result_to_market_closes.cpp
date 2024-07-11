#ifndef DB__MARKET_CLOSE_result_to_market_closes
#define DB__MARKET_CLOSE_result_to_market_closes

#include "lib/utils/string.cpp" // ::utils::string
#include "market_close.h" // DB::MarketClose, market_close_t, query_result_t
#include <list>           // std::list
#include <string>         // std::stod, std::string
#include <vector>         // std::vector

std::list<DB::MarketClose::market_close_t>
DB::MarketClose::result_to_market_closes(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::list<market_close_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    market_close_t record;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "api_key_id") {
        record.api_key_id = value;
      }

      if (field == "closed_at_epoch") {
        record.closed_at = std::stod(value);
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

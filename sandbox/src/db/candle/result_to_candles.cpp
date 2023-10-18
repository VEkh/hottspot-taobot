#ifndef DB__CANDLE_result_to_candles
#define DB__CANDLE_result_to_candles

#include "candle.h"             // DB::Candle, candle_t, query_result_t
#include "lib/utils/string.cpp" // ::utils::string
#include <list>                 // std::list
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

std::list<DB::Candle::candle_t>
DB::Candle::result_to_candles(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::list<candle_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    candle_t record;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "close") {
        record.close = std::stod(value);
      }

      if (field == "closed_at_epoch") {
        record.closed_at = std::stod(value);
      }

      if (field == "high") {
        record.high = std::stod(value);
      }

      if (field == "low") {
        record.low = std::stod(value);
      }

      if (field == "open") {
        record.open = std::stod(value);
      }

      if (field == "opened_at_epoch") {
        record.opened_at = std::stod(value);
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

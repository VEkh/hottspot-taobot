#ifndef DB__HISTORICAL_QUOTE__OANDA_flatten_candles
#define DB__HISTORICAL_QUOTE__OANDA_flatten_candles

#include "deps.cpp" // json
#include "oanda.h"  // DB::HistoricalQuote::Oanda
#include <list>     // std::list
#include <string>   // std::stod, std::string

json DB::HistoricalQuote::Oanda::flatten_candles(json &candles) {
  json flattened = R"([])"_json;

  const std::list<std::string> price_keys = {"o", "h", "l", "c"};

  const double interval_seconds =
      (double)this->granularity_seconds / price_keys.size();

  for (const json candle : candles) {
    const std::string timestamp_string = candle["time"];

    const double opened_at =
        this->db_utils.timestamp_to_epoch(timestamp_string);

    double seconds_from_start = 0;

    for (const std::string key : price_keys) {
      json flattened_candle = R"(
        {
          "ask": 0.0,
          "bid": 0.0,
          "time": 0.0
        }
      )"_json;

      const double epoch = opened_at + seconds_from_start;
      const std::string ask_string = candle["ask"][key];
      const std::string bid_string = candle["bid"][key];

      flattened_candle["ask"] = std::stod(ask_string);
      flattened_candle["bid"] = std::stod(bid_string);
      flattened_candle["time"] = epoch;

      flattened.push_back(flattened_candle);

      seconds_from_start += interval_seconds;
    }
  }

  return flattened;
}

#endif

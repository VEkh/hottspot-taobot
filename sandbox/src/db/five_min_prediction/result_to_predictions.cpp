#ifndef DB__FIVE_MIN_PREDICTION_result_to_predictions
#define DB__FIVE_MIN_PREDICTION_result_to_predictions

#include "five_min_prediction.h" // DB::FiveMinPrediction, prediction_t, query_result_t
#include "lib/utils/string.cpp" // ::utils::string
#include <list>                 // std::list
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

std::list<DB::FiveMinPrediction::prediction_t>
DB::FiveMinPrediction::result_to_predictions(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::list<prediction_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    prediction_t record;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "candle_close") {
        record.candle.close = std::stod(value);
      }

      if (field == "candle_high") {
        record.candle.high = std::stod(value);
      }

      if (field == "candle_low") {
        record.candle.low = std::stod(value);
      }

      if (field == "candle_open") {
        record.candle.open = std::stod(value);
      }

      if (field == "candle_symbol") {
        record.candle.symbol = value;
      }

      if (field == "close") {
        record.close = std::stod(value);
      }

      if (field == "high") {
        record.high = std::stod(value);
      }

      if (field == "low") {
        record.low = std::stod(value);
      }

      if (field == "model_name") {
        record.model_name = value;
      }

      if (field == "open") {
        record.open = std::stod(value);
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

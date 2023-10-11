#ifndef ML__CANDLE_PREDICT_are_predictions_stale
#define ML__CANDLE_PREDICT_are_predictions_stale

#include "candle_predict.h"       // ML::CandlePredict, prediction_t
#include "db/candle/candle.cpp"   // DB::Candle
#include "latest_predictions.cpp" // latest_predictions
#include <list>                   // std::list
#include <utility>                // std::pair

bool ML::CandlePredict::are_predictions_stale(const double current_epoch) {
  std::pair<double, std::list<prediction_t>> latest_predictions_pair =
      latest_predictions();

  DB::Candle::candle_bounds_t current_bounds =
      DB::Candle::timestamp_to_bounds(this->duration_minutes, current_epoch);

  return current_bounds.opened_at != latest_predictions_pair.first;
}

#endif

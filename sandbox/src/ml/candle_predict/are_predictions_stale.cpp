#ifndef ML__CANDLE_PREDICT_are_predictions_stale
#define ML__CANDLE_PREDICT_are_predictions_stale

#include "candle_predict.h"       // ML::CandlePredict
#include "db/candle/candle.cpp"   // DB::Candle
#include "latest_predictions.cpp" // latest_predictions

bool ML::CandlePredict::are_predictions_stale(const double epoch) {
  DB::Candle::candle_bounds_t epoch_bounds =
      DB::Candle::timestamp_to_bounds(this->duration_minutes, epoch);

  return epoch_bounds.opened_at != latest_predictions().first;
}

#endif

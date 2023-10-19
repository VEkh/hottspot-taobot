#ifndef ML__CANDLE_PREDICT_is_ready_to_predict
#define ML__CANDLE_PREDICT_is_ready_to_predict

#include "are_predictions_stale.cpp" // are_predictions_stale
#include "candle_predict.h"          // ML::CandlePredict
#include "latest_predictions.cpp"    // latest_predictions

bool ML::CandlePredict::is_ready_to_predict(const double current_epoch) {
  if (this->predictions.empty()) {
    return false;
  }

  if (are_predictions_stale(current_epoch)) {
    return false;
  }

  const std::list<prediction_t> latest_predictions_ =
      latest_predictions().second;

  if (latest_predictions_.size() < 2) {
    return false;
  }

  return latest_predictions_.size() % 2 != 0;
}

#endif

#ifndef ML__CANDLE_PREDICT_latest_predictions
#define ML__CANDLE_PREDICT_latest_predictions

#include "candle_predict.h" // ML::CandlePredict, predictions_t
#include <map>              // std::map
#include <utility>          // std::pair

std::pair<double, ML::CandlePredict::predictions_t>
ML::CandlePredict::latest_predictions() {
  if (this->predictions.empty()) {
    return {0.0, predictions_t()};
  }

  std::map<double, predictions_t>::reverse_iterator last =
      this->predictions.rbegin();

  return {last->first, last->second};
}

#endif

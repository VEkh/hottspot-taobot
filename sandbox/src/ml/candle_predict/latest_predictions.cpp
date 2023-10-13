#ifndef ML__CANDLE_PREDICT_latest_predictions
#define ML__CANDLE_PREDICT_latest_predictions

#include "candle_predict.h" // ML::CandlePredict, prediction_t
#include <list>             // std::list
#include <map>              // std::map
#include <utility>          // std::pair

std::pair<double, std::list<ML::CandlePredict::prediction_t>>
ML::CandlePredict::latest_predictions() {
  if (this->predictions.empty()) {
    return {0.0, {prediction_t()}};
  }

  std::map<double, std::list<prediction_t>>::reverse_iterator last =
      this->predictions.rbegin();

  return {last->first, last->second};
}

#endif

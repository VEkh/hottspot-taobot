#ifndef ML__CANDLE_PREDICT_predict_at
#define ML__CANDLE_PREDICT_predict_at

#include "candle_predict.h"   // ML::CandlePredict, prediction_t
#include "predict_action.cpp" // predict_action
#include <list>               // std::list
#include <map>                //std::map

ML::CandlePredict::order_action_t
ML::CandlePredict::predict_at(const double epoch) {
  std::list<prediction_t> epoch_predictions;

  std::map<double, std::list<prediction_t>>::reverse_iterator it;

  for (it = this->predictions.rbegin(); it != this->predictions.rend(); it++) {
    if (it->second.front().candle.closed_at <= epoch) {
      epoch_predictions = it->second;

      break;
    }
  }

  return predict_action(epoch_predictions);
}

#endif

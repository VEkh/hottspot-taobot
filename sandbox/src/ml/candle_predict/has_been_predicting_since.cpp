#ifndef ML__CANDLE_PREDICT_has_been_predicting_since
#define ML__CANDLE_PREDICT_has_been_predicting_since

#include "candle_predict.h"   // ML::CandlePredict, order_action_t, prediction_t
#include "predict_action.cpp" // predict_action
#include <list>               // std::list
#include <map>                // std::map

bool ML::CandlePredict::has_been_predicting_since(const double ref_epoch) {
  const int limit = 10;
  int count = 0;

  std::map<double, std::list<prediction_t>>::reverse_iterator it =
      this->predictions.rbegin();

  order_action_t persistent_action = predict_action(it->second);

  for (; it != this->predictions.rend() && count < limit; it++) {
    const order_action_t predicted_action = predict_action(it->second);

    if (predicted_action != persistent_action) {
      break;
    }

    if (it->first < ref_epoch) {
      break;
    }

    count++;
  }

  return count >= limit;
}

#endif

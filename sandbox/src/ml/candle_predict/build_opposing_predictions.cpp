#ifndef ML__CANDLE_PREDICT_build_opposing_predictions
#define ML__CANDLE_PREDICT_build_opposing_predictions

#include "candle_predict.h" // ML::CandlePredict, order_action_t, prediction_t, predictions_t
#include "predict_action.cpp" // predict_action
#include <list>               // std::list
#include <map>                // std::map

void ML::CandlePredict::build_opposing_predictions(
    const order_action_t open_order_action) {
  const order_action_t opposite_action =
      open_order_action == order_action_t::BUY ? order_action_t::SELL
                                               : order_action_t::BUY;

  const int limit = this->OPPOSING_PREDICTIONS_LIMIT;
  int count = 0;

  this->opposing_predictions = {};

  std::map<double, predictions_t>::reverse_iterator it =
      this->predictions.rbegin();

  for (; it != this->predictions.rend() && count != limit; it++) {
    const predictions_t predictions_ = it->second;

    const order_action_t predicted_action =
        predict_action(predictions_.predictions);

    if (predicted_action == opposite_action) {
      this->opposing_predictions[it->first] = predictions_;
      count++;
    }
  }
}

#endif

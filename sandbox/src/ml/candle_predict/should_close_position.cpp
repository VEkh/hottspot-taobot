#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h"   // ML::CandlePredict
#include "predict_action.cpp" // predict_action

bool ML::CandlePredict::should_close_position(
    const order_action_t open_order_action) {
  if (this->predictions.empty()) {
    return false;
  }

  if (this->predictions.size() % 2 == 0) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  return predicted_action != open_order_action;
}

#endif

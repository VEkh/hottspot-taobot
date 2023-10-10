#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h"        // ML::CandlePredict
#include "is_ready_to_predict.cpp" // is_ready_to_predict
#include "predict_action.cpp"      // predict_action

bool ML::CandlePredict::should_close_position(
    const order_action_t open_order_action) {
  if (!is_ready_to_predict()) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  return predicted_action != open_order_action;
}

#endif

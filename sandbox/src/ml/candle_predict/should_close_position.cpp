#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h"                 // ML::CandlePredict, order_action_t
#include "is_profitable_trend_finished.cpp" // is_profitable_trend_finished
#include "is_ready_to_predict.cpp"          // is_ready_to_predict
#include "predict_action.cpp"               // predict_action

bool ML::CandlePredict::should_close_position(
    const double current_mid, const double open_order_profit,
    const order_action_t open_order_action) {
  if (!is_ready_to_predict()) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  if (predicted_action == open_order_action) {
    return false;
  }

  if (open_order_profit < 0) {
    return true;
  }

  if (is_profitable_trend_finished(current_mid, open_order_action)) {
    return true;
  }

  return false;
}

#endif

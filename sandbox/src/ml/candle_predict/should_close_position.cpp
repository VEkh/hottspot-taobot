#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h" // ML::CandlePredict, order_action_t, should_close_position_args_t
#include "is_profitable_trend_finished.cpp" // is_profitable_trend_finished
#include "is_ready_to_predict.cpp"          // is_ready_to_predict
#include "predict_action.cpp"               // predict_action

bool ML::CandlePredict::should_close_position(
    const should_close_position_args_t args) {
  const double open_order_profit = args.open_order_profit;
  const order_action_t open_order_action = args.open_order_action;

  if (!is_ready_to_predict()) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  if (predicted_action == open_order_action) {
    return false;
  }

  if (!this->config.hold_trend) {
    return true;
  }

  if (open_order_profit < 0) {
    return true;
  }

  if (is_profitable_trend_finished(args)) {
    return true;
  }

  return false;
}

#endif

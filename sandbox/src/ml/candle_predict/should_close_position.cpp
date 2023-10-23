#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h" // ML::CandlePredict, order_action_t, should_close_position_args_t, trend_t
#include "is_next_position_long.cpp" // is_next_position_long
#include "is_ready_to_predict.cpp"   // is_ready_to_predict
#include "predict_action.cpp"        // predict_action

bool ML::CandlePredict::should_close_position(
    const should_close_position_args_t args) {
  const order_action_t open_order_action = args.open_order_action;

  if (!is_ready_to_predict(args.current_epoch)) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  return predicted_action != open_order_action;
}
#endif

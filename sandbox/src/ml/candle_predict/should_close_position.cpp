#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h" // ML::CandlePredict, order_action_t, should_close_position_args_t
#include "is_consolidation_range_set.cpp"   // is_consolidation_range_set
#include "is_profitable_trend_finished.cpp" // is_profitable_trend_finished
#include "is_ready_to_predict.cpp"          // is_ready_to_predict
#include "predict_action.cpp"               // predict_action

bool ML::CandlePredict::should_close_position(
    const should_close_position_args_t args) {
  const order_action_t open_order_action = args.open_order_action;

  if (!is_ready_to_predict(args.current_epoch)) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  if (!is_consolidation_range_set()) {
    return predicted_action != open_order_action;
  }

  const double current_mid = args.current_mid;
  const double range_buffer = args.range_buffer;

  if (current_mid > this->consolidation_range.high + range_buffer) {
    return open_order_action != order_action_t::BUY;
  }

  if (current_mid < this->consolidation_range.low - range_buffer) {
    return open_order_action != order_action_t::SELL;
  }

  if (current_mid <= this->consolidation_range.high &&
      current_mid >= this->consolidation_range.low) {
    return predicted_action != open_order_action;
  }

  return false;
}

#endif

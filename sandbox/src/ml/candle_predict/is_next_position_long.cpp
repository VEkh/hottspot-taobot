#ifndef ML__CANDLE_PREDICT_is_next_position_long
#define ML__CANDLE_PREDICT_is_next_position_long

#include "candle_predict.h"               // ML::CandlePredict
#include "is_consolidation_range_set.cpp" // is_consolidation_range_set
#include "predict_action.cpp"             // predict_action

bool ML::CandlePredict::is_next_position_long(
    const is_next_position_long_args_t args) {
  const double current_mid = args.current_mid;
  const double range_buffer = args.range_buffer;

  if (!is_consolidation_range_set()) {
    return predict_action() == order_action_t::BUY;
  }

  if (current_mid > this->consolidation_range.high + range_buffer) {
    return true;
  }

  if (current_mid < this->consolidation_range.low - range_buffer) {
    return false;
  }

  return predict_action() == order_action_t::BUY;
}

#endif

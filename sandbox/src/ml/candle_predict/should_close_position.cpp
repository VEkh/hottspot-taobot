#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h" // ML::CandlePredict, order_action_t, should_close_position_args_t, trend_t
#include "is_consolidation_range_set.cpp" // is_consolidation_range_set
// TODO: Delete
// #include "is_profitable_trend_finished.cpp" // is_profitable_trend_finished
#include "current_trend.cpp"         // current_trend
#include "is_next_position_long.cpp" // is_next_position_long
#include "is_ready_to_predict.cpp"   // is_ready_to_predict
#include "predict_action.cpp"        // predict_action
#include "predict_at.cpp"            // predict_at

// NOTE: Candle Momentum
// bool ML::CandlePredict::should_close_position(
//     const should_close_position_args_t args) {
//   if (!is_ready_to_predict(args.current_epoch)) {
//     return false;
//   }

//   const trend_t trend = current_trend();
//   const bool is_next_action_buy = is_next_position_long();

//   if (args.open_order_action == order_action_t::BUY) {
//     return !is_next_action_buy;
//   }

//   return is_next_action_buy;
// }

// NOTE: Consolidation Range 1
// bool ML::CandlePredict::should_close_position(
//     const should_close_position_args_t args) {
//   const order_action_t open_order_action = args.open_order_action;

//   if (!is_ready_to_predict(args.current_epoch)) {
//     return false;
//   }

//   const order_action_t predicted_action = predict_action();

//   if (args.was_last_position_profit_stopped) {
//     if (predict_at(args.open_order_opened_at) == open_order_action &&
//         predicted_action != open_order_action) {
//       return true;
//     }

//     return false;
//   }

//   if (!is_consolidation_range_set()) {
//     return predicted_action != open_order_action;
//   }

//   const double current_mid = args.current_mid;
//   const double range_buffer = args.range_buffer;

//   if (current_mid > this->consolidation_range.high + range_buffer) {
//     return open_order_action != order_action_t::BUY;
//   }

//   if (current_mid < this->consolidation_range.low - range_buffer) {
//     return open_order_action != order_action_t::SELL;
//   }

//   if (current_mid <= this->consolidation_range.high &&
//       current_mid >= this->consolidation_range.low) {
//     return predicted_action != open_order_action;
//   }

//   return false;
// }

// bool ML::CandlePredict::should_close_position(
//     const should_close_position_args_t args) {
//   const double open_order_profit = args.open_order_profit;
//   const order_action_t open_order_action = args.open_order_action;

//   if (!is_ready_to_predict()) {
//     return false;
//   }

//   const order_action_t predicted_action = predict_action();

//   if (predicted_action == open_order_action) {
//     return false;
//   }

//   if (!this->config.hold_trend) {
//     return true;
//   }

//   if (open_order_profit < 0) {
//     return true;
//   }

//   if (is_profitable_trend_finished(args)) {
//     return true;
//   }

//   return false;
// }

// NOTE: Predictions only
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

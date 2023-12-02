#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h" // ML::CandlePredict, order_action_t, should_close_position_args_t
#include "has_been_predicting_since.cpp"            // has_been_predicting_since
#include "is_ready_to_predict.cpp"                  // is_ready_to_predict
#include "latest_opposite_prediction_closed_at.cpp" // latest_opposite_prediction_closed_at
#include "lib/utils/float.cpp"                      // ::utils::float_
#include "predict_action.cpp"                       // predict_action

bool ML::CandlePredict::should_close_position(
    const should_close_position_args_t args) {
  const double open_order_max_profit = args.open_order_max_profit;
  const double open_order_opened_at = args.open_order_opened_at;
  const double open_order_profit = args.open_order_profit;
  const order_action_t open_order_action = args.open_order_action;

  if (!is_ready_to_predict(args.current_epoch)) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  const bool is_profiting = open_order_profit > 0;
  const double cis_prediction_profit = 0.5 * open_order_max_profit;

  const bool is_cis_prediction_profit_slipping =
      has_been_predicting_since(open_order_opened_at) && is_profiting &&
      open_order_profit <= cis_prediction_profit;

  if (is_cis_prediction_profit_slipping) {
    return true;
  }

  const double latest_opposite_prediction_closed_at_ =
      latest_opposite_prediction_closed_at(this->predictions,
                                           open_order_action);

  if (latest_opposite_prediction_closed_at_ > open_order_opened_at &&
      is_profiting && predicted_action == open_order_action) {
    return true;
  }

  return false;
}
#endif

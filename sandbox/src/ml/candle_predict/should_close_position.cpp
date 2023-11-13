#ifndef ML__CANDLE_PREDICT_should_close_position
#define ML__CANDLE_PREDICT_should_close_position

#include "candle_predict.h" // ML::CandlePredict, order_action_t, should_close_position_args_t
#include "is_ready_to_predict.cpp"                  // is_ready_to_predict
#include "latest_opposite_prediction_closed_at.cpp" // latest_opposite_prediction_closed_at
#include "predict_action.cpp"                       // predict_action

bool ML::CandlePredict::should_close_position(
    const should_close_position_args_t args) {
  const order_action_t open_order_action = args.open_order_action;

  if (!is_ready_to_predict(args.current_epoch)) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  if (!this->config.inverse_predictions) {
    return predicted_action != open_order_action;
  }

  const double open_order_max_profit = args.open_order_max_profit;
  const double open_order_profit = args.open_order_profit;
  const double stop_profit = args.stop_profit;
  const double super_profit = 2.5 * stop_profit;

  const bool is_target_profit_reached = open_order_max_profit >= stop_profit;

  if (!is_target_profit_reached) {
    return false;
  }

  const bool is_super_profit_slipping = open_order_max_profit >= super_profit &&
                                        open_order_profit <= 0.5 * super_profit;

  if (is_super_profit_slipping) {
    return true;
  }

  const double latest_opposite_prediction_closed_at_ =
      latest_opposite_prediction_closed_at(this->predictions,
                                           open_order_action);

  if (latest_opposite_prediction_closed_at_ < args.open_order_opened_at) {
    return false;
  }

  return predicted_action == open_order_action;
}

#endif

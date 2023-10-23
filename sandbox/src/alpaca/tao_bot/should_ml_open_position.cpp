#ifndef ALPACA__TAO_BOT_should_ml_open_position
#define ALPACA__TAO_BOT_should_ml_open_position

#include "current_mid.cpp"                      // current_mid
#include "excess_trigger_buffer.cpp"            // excess_trigger_buffer
#include "ml/candle_predict/candle_predict.cpp" // ML::CandlePredict
#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, position_t

bool Alpaca::TaoBot::should_ml_open_position(ML::CandlePredict &predictor) {
  if (!predictor.is_ready_to_predict(this->current_epoch)) {
    return false;
  }

  if (this->closed_positions.empty()) {
    return true;
  }

  const position_t last_position = this->closed_positions.back();

  if (last_position.close_order.profit >= 0) {
    return true;
  }

  if (last_position.open_order.timestamp <
      predictor.latest_predictions().second.front().candle.closed_at) {
    return true;
  }

  const double current_mid_ = current_mid();
  const double range_buffer = excess_trigger_buffer();

  // Last position lost
  const bool is_next_action_buy = predictor.is_next_position_long();

  if (is_next_action_buy &&
      last_position.open_order.action != order_action_t::BUY) {
    return true;
  }

  if (!is_next_action_buy &&
      last_position.open_order.action == order_action_t::BUY) {
    return true;
  }

  // Prediction matches last position
  bool has_reentered_profit = false;

  if (last_position.open_order.action == order_action_t::BUY) {
    has_reentered_profit =
        current_mid_ >=
        last_position.close_order.execution_price + range_buffer;
  } else {
    has_reentered_profit =
        current_mid_ <=
        last_position.close_order.execution_price - range_buffer;
  }

  return has_reentered_profit;
}

#endif

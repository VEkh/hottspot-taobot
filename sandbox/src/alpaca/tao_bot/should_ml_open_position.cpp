#ifndef ALPACA__TAO_BOT_should_ml_open_position
#define ALPACA__TAO_BOT_should_ml_open_position

#include "current_mid.cpp"                      // current_mid
#include "ml/candle_predict/candle_predict.cpp" // ML::CandlePredict
#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, position_t

bool Alpaca::TaoBot::should_ml_open_position(ML::CandlePredict &predictor) {
  if (!predictor.is_ready_to_predict()) {
    return false;
  }

  if (this->closed_positions.empty()) {
    return true;
  }

  const position_t last_position = this->closed_positions.back();

  if (last_position.close_order.profit >= 0) {
    return true;
  }

  const order_action_t next_direction = predictor.predict_action();

  if (last_position.open_order.action != next_direction) {
    return true;
  }

  const double current_mid_ = current_mid();

  bool has_reentered_profit = false;

  if (last_position.open_order.action == order_action_t::BUY) {
    has_reentered_profit =
        current_mid_ >= last_position.close_order.execution_price +
                            (10 * this->avg_one_sec_variances.running);
  } else {
    has_reentered_profit =
        current_mid_ <= last_position.close_order.execution_price -
                            (10 * this->avg_one_sec_variances.running);
  }

  return has_reentered_profit;
}

#endif

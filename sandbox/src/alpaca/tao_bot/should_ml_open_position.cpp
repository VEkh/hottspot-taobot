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

  if (!predictor.is_consolidation_range_set()) {
    return false;
  }

  return true;
}

#endif

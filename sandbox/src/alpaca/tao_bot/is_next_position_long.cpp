#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "current_mid.cpp"            // current_mid
#include "is_first_position_long.cpp" // is_first_position_long
#include "lib/utils/boolean.cpp"      // ::utils::boolean
#include "tao_bot.h"                  // Alpaca::TaoBot, order_action_t
#include "volatility.cpp"             // volatility

bool Alpaca::TaoBot::is_next_position_long() {
  if (this->closed_positions.empty() &&
      this->candle_predictor.should_predict(volatility())) {
    return this->candle_predictor.is_next_position_long();
  }

  if (this->closed_positions.empty()) {
    return is_first_position_long();
  }

  const position_t last_position = this->closed_positions.back();

  return last_position.close_order.action == order_action_t::BUY;
};

#endif

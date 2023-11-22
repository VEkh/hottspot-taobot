#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "current_mid.cpp"            // current_mid
#include "is_first_position_long.cpp" // is_first_position_long
#include "lib/utils/boolean.cpp"      // ::utils::boolean
#include "tao_bot.h"                  // Alpaca::TaoBot, order_action_t

bool Alpaca::TaoBot::is_next_position_long() {
  if (this->closed_positions.empty() &&
      this->candle_predictor.should_predict()) {
    return this->candle_predictor.is_next_position_long();
  }

  if (this->closed_positions.empty()) {
    return is_first_position_long();
  }

  const position_t last_position = this->closed_positions.back();

  if (this->api_client.config.should_reinvest_win &&
      last_position.close_order.profit > 0) {
    return last_position.open_order.action == order_action_t::BUY;
  }

  return last_position.close_order.action == order_action_t::BUY;
};

#endif

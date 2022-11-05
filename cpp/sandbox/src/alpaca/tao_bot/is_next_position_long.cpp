#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "lib/utils/boolean.cpp" // ::utils::boolean
#include "tao_bot.h"             // Alpaca::TaoBot, order_action_t

bool Alpaca::TaoBot::is_next_position_long() {
  if (!this->closed_positions.size()) {
    return ::utils::boolean::flip_coin();
  }

  const position_t last_position = this->closed_positions.back();

  return last_position.close_order.action == order_action_t::BUY;
};
#endif

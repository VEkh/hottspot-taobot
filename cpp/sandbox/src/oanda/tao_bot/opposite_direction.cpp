#ifndef OANDA__TAO_BOT_opposite_direction
#define OANDA__TAO_BOT_opposite_direction

#include "tao_bot.h" // Oanda::TaoBot

Oanda::TaoBot::order_action_t Oanda::TaoBot::opposite_direction() {
  if (this->is_long_position) {
    return order_action_t::SELL;
  }

  return order_action_t::BUY;
}

#endif

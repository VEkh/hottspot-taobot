#ifndef ALPACA__TAO_BOT_opposite_direction
#define ALPACA__TAO_BOT_opposite_direction

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t

Alpaca::TaoBot::order_action_t
Alpaca::TaoBot::opposite_direction(const order_action_t order_action) {
  return order_action == order_action_t::BUY ? order_action_t::SELL
                                             : order_action_t::BUY;
}

#endif

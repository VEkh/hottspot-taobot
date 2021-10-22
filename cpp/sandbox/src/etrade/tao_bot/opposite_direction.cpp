#ifndef ETRADE__TAO_BOT_opposite_direction
#define ETRADE__TAO_BOT_opposite_direction

#include "tao_bot.h" // ETrade::TaoBot, order_action_t

ETrade::TaoBot::order_action_t
ETrade::TaoBot::opposite_direction(const order_t *order) {
  switch (order->action) {
  case order_action_t::BUY: {
    return order_action_t::SELL_SHORT;
  }
  case order_action_t::SELL_SHORT: {
    return order_action_t::BUY;
  }
  }
}

#endif

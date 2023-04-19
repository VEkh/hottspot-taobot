#ifndef OANDA__TAO_BOT_should_open_position
#define OANDA__TAO_BOT_should_open_position

#include "current_spread.cpp"  // current_spread
#include "is_market_open.cpp"  // is_market_open
#include "is_price_moving.cpp" // is_price_moving
#include "spread_limit.cpp"    // spread_limit
#include "tao_bot.h"           // Oanda::TaoBot, fmt, order_action_t

bool Oanda::TaoBot::should_open_position() {
  return false;

  if (!is_market_open()) {
    return false;
  }

  if (this->open_order_ptr) {
    return false;
  }

  if (current_spread() > spread_limit()) {
    return false;
  }

  if (!this->price_movement.short_term_three_minute_one_second_variance
           .average) {
    return false;
  }

  if (!is_price_moving()) {
    return false;
  }

  return true;
}

#endif

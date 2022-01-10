#ifndef OANDA__TAO_BOT_should_open_position
#define OANDA__TAO_BOT_should_open_position

#include "current_spread.cpp" // current_spread
#include "spread_limit.cpp"   // spread_limit
#include "tao_bot.h"          // Oanda::TaoBot, fmt, order_action_t

bool Oanda::TaoBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  if (current_spread() > spread_limit()) {
    return false;
  }

  return true;
}

#endif

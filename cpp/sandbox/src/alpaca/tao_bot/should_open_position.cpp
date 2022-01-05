#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  if (!this->candlesticks.size()) {
    return false;
  }

  return true;
}

#endif

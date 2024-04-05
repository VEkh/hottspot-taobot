#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "is_entry_signal_present.cpp" // is_entry_signal_present
#include "is_market_open.cpp"          // is_market_open
#include "tao_bot.h"                   // Alpaca::TaoBot

bool Alpaca::TaoBot::should_open_position() {
  if (!is_market_open()) {
    return false;
  }

  if (this->open_order_ptr) {
    return false;
  }

  return is_entry_signal_present();
}

#endif

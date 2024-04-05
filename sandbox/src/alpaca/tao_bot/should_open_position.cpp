#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "does_position_exist.cpp"       // does_position_exist
#include "is_entry_signal_present.cpp"   // is_entry_signal_present
#include "is_market_open.cpp"            // is_market_open
#include "should_use_price_movement.cpp" // should_use_price_movement
#include "tao_bot.h"                     // Alpaca::TaoBot

bool Alpaca::TaoBot::should_open_position() {
  if (!is_market_open()) {
    return false;
  }

  if (this->open_order_ptr) {
    return false;
  }

  if (this->api_client.config.should_await_reversal_indicator) {
    return is_entry_signal_present();
  }

  return true;
}

#endif

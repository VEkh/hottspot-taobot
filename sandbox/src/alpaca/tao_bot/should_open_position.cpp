#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "has_already_stopped_profit.cpp" // has_already_stopped_profit // TODO: Decide
#include "is_entry_signal_present.cpp" // is_entry_signal_present
#include "tao_bot.h"                   // Alpaca::TaoBot

bool Alpaca::TaoBot::should_open_position() {
  if (!this->market_availability.is_market_open(this->current_epoch)) {
    return false;
  }

  if (this->open_order_ptr) {
    return false;
  }

  // TODO: Decide
  if (has_already_stopped_profit()) {
    return false;
  }

  return is_entry_signal_present();
}

#endif

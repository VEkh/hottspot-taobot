#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "is_entry_signal_present.cpp" // is_entry_signal_present
#include "is_spike_entry_signal_present.cpp" // is_spike_entry_signal_present // TODO: Decide

#include "can_open_position.cpp" // can_open_position
#include "tao_bot.h"             // Alpaca::TaoBot

bool Alpaca::TaoBot::should_open_position() {
  if (!can_open_position()) {
    return false;
  }

  // TODO: Decide
  if (this->api_client.config.should_enter_at_spike) {
    return is_spike_entry_signal_present();
  }

  return is_entry_signal_present();
}

#endif

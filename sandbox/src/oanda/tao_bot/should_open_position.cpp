#ifndef OANDA__TAO_BOT_should_open_position
#define OANDA__TAO_BOT_should_open_position

#include "can_open_position.cpp"       // can_open_position
#include "is_entry_signal_present.cpp" // is_entry_signal_present
#include "tao_bot.h"                   // Oanda::TaoBot, fmt, order_action_t

#include "is_non_spike_entry_signal_present.cpp" // is_non_spike_entry_signal_present // TODO: Decide

bool Oanda::TaoBot::should_open_position() {
  if (!can_open_position()) {
    return false;
  }

  // TODO: Decide
  if (!this->api_client.config.should_enter_at_spike) {
    return is_non_spike_entry_signal_present();
  }

  return is_entry_signal_present();
}

#endif

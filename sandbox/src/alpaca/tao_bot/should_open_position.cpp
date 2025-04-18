#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "can_open_position.cpp"                    // can_open_position
#include "is_entry_signal_present.cpp"              // is_entry_signal_present
#include "is_record_break_entry_signal_present.cpp" // is_record_break_entry_signal_present
#include "tao_bot.h"                                // Alpaca::TaoBot

bool Alpaca::TaoBot::should_open_position() {
  if (!can_open_position()) {
    return false;
  }

  if (this->api_client.config.should_await_record_break) {
    return is_record_break_entry_signal_present();
  }

  return is_entry_signal_present();
}

#endif

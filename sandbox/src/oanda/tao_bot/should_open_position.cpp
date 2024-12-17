#ifndef OANDA__TAO_BOT_should_open_position
#define OANDA__TAO_BOT_should_open_position

#include "can_open_position.cpp" // can_open_position
#include "tao_bot.h"             // Oanda::TaoBot, fmt, order_action_t

bool Oanda::TaoBot::should_open_position() {
  if (!can_open_position()) {
    return false;
  }

  return is_entry_signal_present();
}

#endif

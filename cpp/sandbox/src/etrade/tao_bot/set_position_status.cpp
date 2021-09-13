#if !defined ETRADE__TAO_BOT_set_position_status
#define ETRADE__TAO_BOT_set_position_status

#include "set_status.cpp" // set_status
#include "tao_bot.h"    // ETrade::TaoBot

void ETrade::TaoBot::set_position_status() {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  set_status(this->open_order_ptr);
  set_status(this->close_order_ptr);
}

#endif

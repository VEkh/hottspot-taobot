#ifndef ALPACA__TAO_BOT_set_position_status
#define ALPACA__TAO_BOT_set_position_status

#include "set_status.cpp" // set_status
#include "tao_bot.h"      // Alpaca::TaoBot

void Alpaca::TaoBot::set_position_status() {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  set_status(this->open_order_ptr);
  set_status(this->close_order_ptr);
}

#endif

#ifndef OANDA__TAO_BOT_set_position_status
#define OANDA__TAO_BOT_set_position_status

#include "complete_filled_order.cpp" // complete_filled_order
#include "set_status.cpp"            // set_status
#include "tao_bot.h"                 // Oanda::TaoBot

void Oanda::TaoBot::set_position_status() {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  puts("OANDA__TAO_BOT_set_position_status");
  std::cout << std::flush;

  set_status(this->open_order_ptr);
  complete_filled_order(this->open_order_ptr);

  set_status(this->close_order_ptr);
  complete_filled_order(this->close_order_ptr);
}

#endif

#ifndef OANDA__TAO_BOT_set_close_order_prices
#define OANDA__TAO_BOT_set_close_order_prices

#include "set_execution_price.cpp"  // set_execution_price
#include "set_profit.cpp"           // set_profit
#include "tao_bot.h"                // Oanda::TaoBot, fmt, order_status_t
#include "write_close_position.cpp" // write_close_position

void Oanda::TaoBot::set_close_order_prices() {
  if (!this->close_order_ptr || !this->open_order_ptr) {
    return;
  }

  if (this->close_order.status != order_status_t::ORDER_FILLED) {
    return;
  }

  set_execution_price(this->close_order_ptr);
  set_profit(this->close_order_ptr, this->open_order_ptr);
  write_close_position();
}

#endif

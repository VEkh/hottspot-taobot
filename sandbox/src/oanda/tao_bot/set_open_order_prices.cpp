#ifndef OANDA__TAO_BOT_set_open_order_prices
#define OANDA__TAO_BOT_set_open_order_prices

#include "set_execution_price.cpp" // set_execution_price
#include "set_profit.cpp"          // set_profit
#include "tao_bot.h"               // Oanda::TaoBot, fmt, order_status_t
#include "write_open_position.cpp" // write_open_position

void Oanda::TaoBot::set_open_order_prices() {
  if (!this->open_order_ptr) {
    return;
  }

  if (this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  set_execution_price(this->open_order_ptr);
  set_profit(this->open_order_ptr);
  write_open_position();
}

#endif

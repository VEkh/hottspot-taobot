#ifndef ETRADE__TAO_BOT_set_close_position_prices
#define ETRADE__TAO_BOT_set_close_position_prices

#include "set_execution_price.cpp" // set_execution_price
#include "set_profit.cpp"          // set_profit
#include "tao_bot.h"               // ETrade::TaoBot, fmt, order_status_t

void ETrade::TaoBot::set_close_position_prices() {
  if (!this->close_order_ptr || !this->open_order_ptr) {
    return;
  }

  if (this->close_order.status != order_status_t::ORDER_EXECUTED) {
    return;
  }

  set_execution_price(this->close_order_ptr);
  set_profit(this->close_order_ptr, this->open_order_ptr);
}

#endif

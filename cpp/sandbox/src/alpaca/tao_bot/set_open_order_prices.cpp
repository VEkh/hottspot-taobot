#ifndef ALPACA__TAO_BOT_set_open_order_prices
#define ALPACA__TAO_BOT_set_open_order_prices

/*
 * Alpaca::TaoBot
 * order_status_t
 * order_t
 * quote_t
 */
#include "tao_bot.h"

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "set_execution_price.cpp"  // set_execution_price
#include "set_profit.cpp"           // set_profit
#include "write_open_position.cpp"  // write_open_position
#include <vector>                   // std::vector

void Alpaca::TaoBot::set_open_order_prices() {
  // TODO: Delete Backtest Guard
  if (this->backtest.is_active) {
    return;
  }

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

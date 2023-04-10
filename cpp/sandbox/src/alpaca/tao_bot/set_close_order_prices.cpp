#ifndef ALPACA__TAO_BOT_set_close_order_prices
#define ALPACA__TAO_BOT_set_close_order_prices

#include "set_execution_price.cpp"  // set_execution_price
#include "set_profit.cpp"           // set_profit
#include "tao_bot.h"                // Alpaca::TaoBot, order_status_t, order_t
#include "write_close_position.cpp" // write_close_position

void Alpaca::TaoBot::set_close_order_prices() {
  // TODO: Delete Backtest Guard
  if (this->api_client.config.is_backtest) {
    return;
  }

  if (!this->close_order_ptr || !this->open_order_ptr) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  set_execution_price(this->close_order_ptr);
  set_profit(this->close_order_ptr, this->open_order_ptr);
  write_close_position();
}

#endif

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
#include <vector>                   // std::vector

void Alpaca::TaoBot::set_open_order_prices() {
  if (!this->open_order_ptr) {
    return;
  }

  if (this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  const std::vector<quote_t> *quotes_ptr =
      &this->quotes[this->open_order_ptr->symbol];

  set_execution_price(this->api_client, this->open_order_ptr);
  set_profit(this->open_order_ptr, quotes_ptr);
}

#endif

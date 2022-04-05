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

void Alpaca::TaoBot::set_open_order_prices(
    Alpaca::Client &api_client_ref, order_t *order_ptr,
    const std::vector<quote_t> *quotes_ptr) {
  if (!order_ptr) {
    return;
  }

  if (order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  set_execution_price(api_client_ref, order_ptr);
  set_profit(order_ptr, quotes_ptr);
}

#endif

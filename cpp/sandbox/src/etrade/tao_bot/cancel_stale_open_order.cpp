#ifndef ETRADE__TAO_BOT_cancel_stale_open_order
#define ETRADE__TAO_BOT_cancel_stale_open_order

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // ETrade::TaoBot, order_status_t
#include <iostream>          // std::cout, std::endl
#include <stdio.h>           // printf

void ETrade::TaoBot::cancel_stale_open_order() {
  if (!this->open_order_ptr) {
    return;
  }

  if (this->open_order.status != order_status_t::ORDER_OPEN) {
    return;
  }

  const bool is_order_stale =
      (current_price() - this->open_order.limit_price) >=
      this->average_tick_price_delta * 25.0;

  if (!is_order_stale) {
    return;
  }

  std::cout << fmt.yellow << fmt.bold;
  printf("😴 Cancelling stale open order %i.\n", this->open_order.id);
  std::cout << fmt.reset;

  this->api_client.cancel_order(this->open_order_ptr);
  this->open_order_ptr = nullptr;
}

#endif

#ifndef OANDA__TAO_BOT_clear_stale_open_order
#define OANDA__TAO_BOT_clear_stale_open_order

#include "reset_orders.cpp" // reset_orders
#include "tao_bot.h"        // Oanda::TaoBot, order_status_t
#include <ctime>            // std::time, std::time_t
#include <iostream>         // std::cout, std::endl
#include <stdio.h>          // printf

void Oanda::TaoBot::clear_stale_open_order() {
  if (!this->open_order_ptr) {
    return;
  }

  if (this->backtest.is_active) {
    return;
  }

  if (this->open_order_ptr->status == order_status_t::ORDER_CANCELLED) {
    std::cout << fmt.yellow << fmt.bold;
    printf("🔁 Resetting cancelled order %i.\n", this->open_order_ptr->id);
    std::cout << fmt.reset;

    reset_orders();

    return;
  }

  if (this->open_order_ptr->status != order_status_t::ORDER_PENDING) {
    return;
  }

  const std::time_t now = std::time(nullptr);
  const int time_limit = 10;

  const bool is_order_stale =
      (now - this->open_order_ptr->timestamp) >= time_limit;

  if (!is_order_stale) {
    return;
  }

  std::cout << fmt.yellow << fmt.bold;
  printf("⛔ Cancelling stale open order %i.\n", this->open_order_ptr->id);
  std::cout << fmt.reset;

  this->api_client.cancel_order(this->open_order_ptr);
}

#endif

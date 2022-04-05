#ifndef OANDA__TAO_BOT_clear_stale_open_order
#define OANDA__TAO_BOT_clear_stale_open_order

#include "tao_bot.h" // Oanda::TaoBot, order_status_t
#include <ctime>     // std::time, std::time_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf

void Oanda::TaoBot::clear_stale_open_order() {
  if (!this->open_order_ptr) {
    return;
  }

  if (!(this->open_order.status == order_status_t::ORDER_PENDING ||
        this->open_order.status == order_status_t::ORDER_CANCELLED)) {
    return;
  }

  const std::time_t now = std::time(nullptr);
  const int time_limit = 10;

  const bool is_order_stale = (now - this->open_order.timestamp) >= time_limit;

  if (!is_order_stale) {
    return;
  }

  switch (this->open_order.status) {
  case order_status_t::ORDER_CANCELLED: {
    std::cout << fmt.yellow << fmt.bold;
    printf("😴 Clearing stale open order %i.\n", this->open_order.id);
    std::cout << fmt.reset;

    this->open_order_ptr = nullptr;

    break;
  }
  case order_status_t::ORDER_PENDING: {
    std::cout << fmt.yellow << fmt.bold;
    printf("⛔ Cancelling stale open order %i.\n", this->open_order.id);
    std::cout << fmt.reset;

    this->api_client.cancel_order(this->open_order_ptr);

    std::cout << fmt.yellow << fmt.bold;
    printf("🛑 This is probably an error. Investigate it.\n");
    std::cout << fmt.reset;

    exit(1);

    break;
  }
  }
}

#endif

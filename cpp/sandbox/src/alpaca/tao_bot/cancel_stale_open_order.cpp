#ifndef ALPACA__TAO_BOT_cancel_stale_open_order
#define ALPACA__TAO_BOT_cancel_stale_open_order

#include "tao_bot.h" // Alpaca::TaoBot, order_status_t
#include <ctime>     // std::time, std::time_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf

void Alpaca::TaoBot::cancel_stale_open_order() {
  if (!this->open_order_ptr) {
    return;
  }

  if (this->open_order.status == order_status_t::ORDER_CANCELED) {
    this->open_order_ptr = nullptr;

    return;
  }

  if (!(this->open_order.status == order_status_t::ORDER_NEW ||
        this->open_order.status == order_status_t::ORDER_CANCELED)) {
    return;
  }

  const std::time_t now = std::time(nullptr);
  const int time_limit = 10;

  const bool is_order_stale = (now - this->open_order.timestamp) >= time_limit;

  if (!is_order_stale) {
    return;
  }

  std::cout << fmt.yellow << fmt.bold;
  printf("😴 Clearing stale open order %s.\n", this->open_order.id.c_str());
  std::cout << fmt.reset;

  this->api_client.cancel_order(this->open_order_ptr);
}

#endif

#ifndef OANDA__TAO_BOT_cancel_stale_open_order
#define OANDA__TAO_BOT_cancel_stale_open_order

#include "tao_bot.h" // Oanda::TaoBot, order_status_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf
#include <time.h>    // time, time_t

void Oanda::TaoBot::cancel_stale_open_order() {
  if (!this->open_order_ptr) {
    return;
  }

  time_t now;
  time(&now);

  if (this->open_order.status == order_status_t::ORDER_PENDING &&
      now - this->open_order.timestamp >= 30) {
    std::cout << fmt.yellow << fmt.bold;
    printf("😴 Cancelling stale open order %i.\n", this->open_order.id);
    std::cout << fmt.reset;

    this->api_client.cancel_order(this->open_order_ptr);
    this->open_order_ptr = nullptr;
  }
}

#endif

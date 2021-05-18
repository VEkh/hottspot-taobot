#ifndef ETRADE__STOCK_BOT_cancel_stale_open_order
#define ETRADE__STOCK_BOT_cancel_stale_open_order

#include "stock_bot.h" // ETrade::StockBot, order_status_t
#include <iostream>    // time, time_t
#include <time.h>      // time, time_t

void ETrade::StockBot::cancel_stale_open_order() {
  if (!this->open_order_ptr) {
    return;
  }

  time_t now;
  time(&now);

  if (this->open_order.status == order_status_t::ORDER_OPEN &&
      now - this->open_order.timestamp >= 30) {
    std::cout << fmt.yellow << fmt.bold;
    std::cout << "😴 Cancelling stale open order " << this->open_order.id << ".";
    std::cout << std::endl;
    std::cout << fmt.reset;

    this->etrade_client.cancel_order(this->open_order_ptr);
    this->open_order_ptr = nullptr;
  }
}

#endif

#ifndef ETRADE__STOCK_BOT_reset_position
#define ETRADE__STOCK_BOT_reset_position

/*
 * ETrade::StockBot
 * order_status_t
 */
#include "stock_bot.h"

#include "lib/transmission/transmission.cpp" // Transmission
#include <time.h>                            // time, time_t

void ETrade::StockBot::reset_position() {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  if (this->open_order.status != order_status_t::ORDER_EXECUTED ||
      this->close_order.status != order_status_t::ORDER_EXECUTED) {
    return;
  }

  time_t now;
  time(&now);

  position_t new_position = {
      .close_order = this->close_order,
      .close_timestamp = (int)now,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(new_position);

  this->close_order_ptr = nullptr;
  this->open_order_ptr = nullptr;
  this->transmission = Transmission();
}

#endif

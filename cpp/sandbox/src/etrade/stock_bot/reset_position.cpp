#ifndef ETRADE__STOCK_BOT_reset_position
#define ETRADE__STOCK_BOT_reset_position

/*
 * ETrade::StockBot
 * order_status_t
 * order_win_result_t
 */
#include "stock_bot.h"

#include "order_win_result.cpp" // order_win_result
#include <time.h>               // time, time_t

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

  position_t position = {
      .close_order = this->close_order,
      .close_timestamp = (int)now,
      .open_order = this->open_order,
  };

  if (this->FLAG_MARTINGALE) {
    const order_win_result_t win_result =
        order_win_result(&(this->close_order));

    switch (win_result) {
    case order_win_result_t::LOSS: {
      this->martingale_quantity_multiplier *= 2;

      break;
    }

    case order_win_result_t::WIN: {
      this->martingale_profit_multiplier = 1;
      this->martingale_quantity_multiplier = 1;

      break;
    }
    }
  }

  this->closed_positions.push_back(position);
  this->close_order_ptr = nullptr;
  this->open_order_ptr = nullptr;
}

#endif

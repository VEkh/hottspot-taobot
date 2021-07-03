#ifndef ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * exit_prices_t
 * order_status_t
 */
#include "stock_bot.h"

#include "build_exit_prices.cpp" // build_exit_prices
#include "lib/utils/time.cpp"    // utils::time_
#include "profit_percentage.cpp" // profit_percentage
#include <time.h>                // time, time_t

bool ETrade::StockBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
    return false;
  }

  if (utils::time_::is_end_of_day()) {
    return true;
  }

  this->exit_prices = build_exit_prices();

  if (this->open_order.max_profit >= this->exit_prices.min_profit &&
      this->open_order.profit >= this->exit_prices.secure_profit_lower &&
      this->open_order.profit <= this->exit_prices.secure_profit_upper) {
    return true;
  }

  if (this->open_order.profit <= exit_prices.max_loss) {
    return true;
  }

  return false;
}

#endif

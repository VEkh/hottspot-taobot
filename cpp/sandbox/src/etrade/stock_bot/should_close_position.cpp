#ifndef ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * gear_t
 * order_status_t
 */
#include "stock_bot.h"

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

  const double trailing_stop = 0.2;
  const double max_loss_multiplier = 15.0;
  const double min_profit_multiplier = 15.0 / (1 - trailing_stop);
  const double max_loss = max_loss_multiplier * this->average_tick_price_delta;
  const double min_profit =
      min_profit_multiplier * this->average_tick_price_delta;

  if (this->open_order.max_profit >= min_profit &&
      this->open_order.profit >= 0.5 * this->open_order.max_profit &&
      this->open_order.profit <=
          (1 - trailing_stop) * this->open_order.max_profit) {
    return true;
  }

  if (this->open_order.profit <= -max_loss) {
    return true;
  }

  return false;
}

#endif

#ifndef ETRADE__TAO_BOT_should_close_position
#define ETRADE__TAO_BOT_should_close_position

/*
 * ETrade::TaoBot
 * order_status_t
 */
#include "tao_bot.h"

#include "build_exit_prices.cpp"        // build_exit_prices
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period

bool ETrade::TaoBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
    return false;
  }

  if (is_end_of_trading_period()) {
    return true;
  }

  this->exit_prices = build_exit_prices();

  if (this->open_order.max_profit >= this->exit_prices.min_profit &&
      this->open_order.profit >= this->exit_prices.lower_secure_profit &&
      this->open_order.profit <= this->exit_prices.upper_secure_profit) {
    return true;
  }

  if (this->open_order.profit <= exit_prices.max_loss) {
    return true;
  }

  return false;
}

#endif

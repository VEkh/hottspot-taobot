#ifndef OANDA__TAO_BOT_should_close_position
#define OANDA__TAO_BOT_should_close_position

/*
 * Oanda::TaoBot
 * order_status_t
 */
#include "tao_bot.h"

#include "build_exit_prices.cpp"        // build_exit_prices
#include "compute_profit.cpp"           // compute_profit
#include "current_spread.cpp"           // current_spread
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "opposite_direction.cpp"       // opposite_direction
#include "should_open_position.cpp"     // should_open_position

bool Oanda::TaoBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_FILLED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_INIT) {
    return false;
  }

  if (is_end_of_trading_period()) {
    return true;
  }

  this->exit_prices = build_exit_prices();

  if (should_open_position(this->open_order.action)) {
    return false;
  }

  if (this->open_order.max_profit >= this->exit_prices.min_profit &&
      this->open_order.profit >= this->exit_prices.lower_secure_profit &&
      this->open_order.profit <= this->exit_prices.upper_secure_profit) {
    return true;
  }

  if (this->open_order.profit >
      (-10.0 * this->average_tick_price_delta - current_spread())) {
    return false;
  }

  if (should_open_position(opposite_direction(this->open_order_ptr))) {
    return true;
  }

  return false;
}

#endif

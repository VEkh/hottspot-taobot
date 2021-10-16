#ifndef OANDA__TAO_BOT_should_close_position
#define OANDA__TAO_BOT_should_close_position

/*
 * Oanda::TaoBot
 * order_action_t
 * order_status_t
 * quote_t
 */
#include "tao_bot.h"

#include "build_exit_prices.cpp"        // build_exit_prices
#include "compute_profit.cpp"           // compute_profit
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
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

  const quote_t previous_quote = this->quotes.at(this->quotes.size() - 2);
  const double previous_profit =
      compute_profit(this->open_order_ptr, &previous_quote);

  if (this->open_order.max_profit >= this->exit_prices.min_profit &&
      previous_profit >= this->exit_prices.secure_profit &&
      this->open_order.profit <= this->exit_prices.secure_profit) {
    return true;
  }

  if (this->open_order.profit > -10.0 * this->average_tick_price_delta) {
    return false;
  }

  if (this->is_long_position && should_open_position(order_action_t::SELL)) {
    return true;
  }

  if (!this->is_long_position && should_open_position(order_action_t::BUY)) {
    return true;
  }

  return false;
}

#endif

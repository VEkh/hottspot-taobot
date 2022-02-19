#ifndef OANDA__TAO_BOT_should_close_position
#define OANDA__TAO_BOT_should_close_position

/*
 * Oanda::TaoBot
 * order_status_t
 */
#include "tao_bot.h"

#include "build_exit_prices.cpp"        // build_exit_prices
#include "current_spread.cpp"           // current_spread
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "spread_limit.cpp"             // spread_limit

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

  if (max_account_loss_reached()) {
    return true;
  }

  if (current_spread() > spread_limit()) {
    return false;
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

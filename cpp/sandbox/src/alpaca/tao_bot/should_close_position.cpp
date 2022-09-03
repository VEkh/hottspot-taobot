#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

#include "build_exit_prices.cpp"        // build_exit_prices
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "should_stop_profit.cpp"       // should_stop_profit
#include "tao_bot.h"                    // Alpaca::TaoBot, order_status_t

bool Alpaca::TaoBot::should_close_position() {
  if (this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return false;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_INIT) {
    return false;
  }

  if (is_end_of_trading_period()) {
    return true;
  }

  if (max_account_loss_reached()) {
    return true;
  }

  if (should_stop_profit()) {
    return true;
  }

  this->exit_prices = build_exit_prices();

  if (this->open_order_ptr->max_profit >= this->exit_prices.min_profit &&
      this->open_order_ptr->profit > 0 &&
      this->open_order_ptr->profit < this->exit_prices.trailing_stop_profit) {
    return true;
  }

  if (this->open_order_ptr->profit <= this->exit_prices.max_loss) {
    return true;
  }

  return false;
}

#endif

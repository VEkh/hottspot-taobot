#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

#include "alpaca/utils.cpp"             // Alpaca::Utils
#include "build_exit_prices.cpp"        // build_exit_prices
#include "current_mid.cpp"              // current_mid
#include "does_position_exist.cpp"      // does_position_exist
#include "is_trending.cpp"              // is_trending
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

  if (Alpaca::Utils::is_end_of_trading_period(this->current_epoch)) {
    return true;
  }

  if (max_account_loss_reached()) {
    return true;
  }

  if (this->backtest.is_active &&
      this->backtest.has_reached_end(this->current_epoch)) {
    return true;
  }

  this->exit_prices = build_exit_prices();

  if (should_stop_profit()) {
    return true;
  }

  if (this->exit_prices.stop_loss &&
      this->open_order_ptr->profit <= this->exit_prices.stop_loss) {
    return true;
  }

  if (this->exit_prices.stop_profit &&
      this->open_order_ptr->max_profit >= this->exit_prices.stop_profit &&
      this->open_order_ptr->profit > 0 &&
      this->open_order_ptr->profit <= this->exit_prices.trailing_stop_profit) {
    return true;
  }

  return false;
}

#endif

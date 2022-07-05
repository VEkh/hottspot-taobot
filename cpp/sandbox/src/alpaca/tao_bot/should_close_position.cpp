#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

#include "build_exit_prices.cpp"        // build_exit_prices
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "should_stop_profit.cpp"       // should_stop_profit
#include "tao_bot.h"                    // Alpaca::TaoBot, order_status_t

bool Alpaca::TaoBot::should_close_position(const order_t *close_order_ptr_,
                                           const order_t *open_order_ptr_) {
  if (open_order_ptr_->status != order_status_t::ORDER_FILLED) {
    return false;
  }

  if (close_order_ptr_->status != order_status_t::ORDER_INIT) {
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

  this->exit_prices = build_exit_prices(open_order_ptr_);

  if (open_order_ptr_->profit > this->exit_prices.min_profit &&
      open_order_ptr_->profit < open_order_ptr_->max_profit) {
    return true;
  }

  if (open_order_ptr_->profit <= this->exit_prices.max_loss) {
    return true;
  }

  return false;
}

#endif

#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

/*
 * Alpaca::TaoBot
 * order_status_t
 */
#include "tao_bot.h"

#include "build_exit_prices.cpp"        // build_exit_prices
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "position_target_movement.cpp" // position_target_movement
#include <math.h>                       // abs

bool Alpaca::TaoBot::should_close_position(
    const order_t *close_order_ptr_, order_t *open_order_ptr_,
    const order_t *opposite_close_order_ptr = nullptr,
    const order_t *opposite_open_order_ptr = nullptr) {
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

  this->exit_prices = build_exit_prices(
      open_order_ptr_, opposite_close_order_ptr, opposite_open_order_ptr);

  if (open_order_ptr_->max_profit >= this->exit_prices.min_profit &&
      open_order_ptr_->profit >= this->exit_prices.lower_secure_profit &&
      open_order_ptr_->profit <= this->exit_prices.upper_secure_profit) {
    return true;
  }

  if (open_order_ptr_->profit <= exit_prices.max_loss) {
    return true;
  }

  return false;
}

#endif

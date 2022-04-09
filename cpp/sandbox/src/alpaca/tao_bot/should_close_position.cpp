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
#include "open_position_profit.cpp"     // open_position_profit
#include <algorithm>                    // std::min

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

  this->exit_prices =
      build_exit_prices(this->open_order_ptr, this->hedge_close_order_ptr);

  const position_t current_position = {
      .close_order = this->close_order,
      .hedge_close_order = this->hedge_close_order,
      .hedge_open_order = this->hedge_open_order,
      .open_order = this->open_order,
  };

  const double open_position_profit_ =
      open_position_profit(this->open_order_ptr, this->hedge_open_order_ptr);

  if (open_position_profit_ >= this->exit_prices.min_profit) {
    return true;
  }

  return false;
}

#endif

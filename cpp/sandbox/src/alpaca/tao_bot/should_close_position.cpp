#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

/*
 * Alpaca::TaoBot
 * order_status_t
 */
#include "tao_bot.h"

#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "max_loss_ratio.cpp"           // max_loss_ratio
#include "open_position_profit.cpp"     // open_position_profit
#include "opposite_direction.cpp"       // opposite_direction
#include "profit_duration.cpp"          // profit_duration
#include "take_profit_after.cpp"        // take_profit_after
#include <ctime>                        // std::time

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

  const double open_position_profit_ = open_position_profit(open_order_ptr_);

  if (open_position_profit_ > 0 && profit_duration(this->profit_started_at) >=
                                       take_profit_after(open_order_ptr_)) {
    return true;
  }

  if (open_position_profit_ < 0 &&
      profit_duration(this->loss_started_at) >= 5 * 60) {
    return true;
  }

  const double profit_ratio =
      open_order_ptr_->profit / open_order_ptr_->execution_price;

  if (profit_ratio <= max_loss_ratio(open_order_ptr_)) {
    return true;
  }

  return false;
}

#endif

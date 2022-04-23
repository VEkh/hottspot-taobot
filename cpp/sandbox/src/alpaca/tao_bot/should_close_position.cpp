#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

/*
 * Alpaca::TaoBot
 * order_status_t
 */
#include "tao_bot.h"

#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "open_position_profit.cpp"     // open_position_profit
#include "profit_duration.cpp"          // profit_duration

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

  const double open_position_profit_ =
      open_position_profit(this->open_order_ptr);

  if (open_position_profit_ > 0 &&
      profit_duration(this->profit_started_at) >= 20) {
    return true;
  }

  const double converted_signaler_price_ = converted_signaler_price();
  const double signaled_price = current_price(this->signal.signaled);

  if (open_order_ptr_->action == order_action_t::BUY &&
      converted_signaler_price_ <= signaled_price) {
    return true;
  }

  if (open_order_ptr_->action == order_action_t::SELL &&
      converted_signaler_price_ >= signaled_price) {
    return true;
  }

  return false;
}

#endif

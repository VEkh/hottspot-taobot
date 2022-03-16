#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "position_target_movement.cpp" // position_target_movement
#include "secured_profit_ratio.cpp"     // secured_profit_ratio
#include "tao_bot.h"                    // Alpaca::TaoBot
#include <algorithm>                    // std::max std::min
#include <math.h>                       // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices(
    const order_t *open_order_ptr_,
    const order_t *opposite_close_order_ptr = nullptr) {
  double max_loss = this->exit_prices.max_loss ? this->exit_prices.max_loss
                                               : -position_target_movement();

  const double secured_profit_ratio_ = secured_profit_ratio(open_order_ptr_);

  if (opposite_close_order_ptr &&
      opposite_close_order_ptr->status == order_status_t::ORDER_FILLED) {
    max_loss = std::min(
        max_loss, (opposite_close_order_ptr->profit / secured_profit_ratio_));
  }

  const double init_max_loss = this->exit_prices.init_max_loss
                                   ? this->exit_prices.init_max_loss
                                   : max_loss;

  const double min_profit = abs(max_loss) / secured_profit_ratio_;
  const double lower_secure_profit = min_profit * secured_profit_ratio_;

  const double upper_secure_profit =
      open_order_ptr_ == nullptr
          ? 0
          : std::max(this->exit_prices.upper_secure_profit,
                     open_order_ptr_->max_profit * secured_profit_ratio_);

  return {
      .init_max_loss = init_max_loss,
      .lower_secure_profit = lower_secure_profit,
      .max_loss = max_loss,
      .min_profit = min_profit,
      .upper_secure_profit = upper_secure_profit,
  };
}

#endif

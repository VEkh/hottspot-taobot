#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "position_target_movement.cpp" // position_target_movement
#include "secured_profit_ratio.cpp"     // secured_profit_ratio
#include "tao_bot.h"                    // Alpaca::TaoBot, fmt
#include <algorithm>                    // std::max std::min
#include <iostream>                     // std::cout, std::endl
#include <math.h>                       // INFINITY
#include <stdio.h>                      // puts

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices(
    order_t *open_order_ptr_,
    const order_t *opposite_close_order_ptr = nullptr) {
  double position_target_movement_ = position_target_movement();
  double max_loss = -position_target_movement_;
  double min_profit = INFINITY;
  double lower_secure_profit = INFINITY;
  double upper_secure_profit = INFINITY;

  if (opposite_close_order_ptr &&
      opposite_close_order_ptr->status == order_status_t::ORDER_FILLED &&
      opposite_close_order_ptr->profit) {
    if (!open_order_ptr_->max_profit_reset) {
      open_order_ptr_->max_profit_reset = true;
      this->exit_prices.position_target_movement = 0;
      this->exit_prices.upper_secure_profit = -INFINITY;
    }

    position_target_movement_ = this->exit_prices.position_target_movement
                                    ? this->exit_prices.position_target_movement
                                    : position_target_movement();

    const double secured_profit_ratio_ = secured_profit_ratio(open_order_ptr_);
    const double target_profit = position_target_movement_;

    const double raw_min_profit =
        target_profit - opposite_close_order_ptr->profit;

    max_loss = -target_profit - opposite_close_order_ptr->profit;
    min_profit = raw_min_profit / secured_profit_ratio_;
    lower_secure_profit = min_profit * secured_profit_ratio_;
    upper_secure_profit =
        std::max(this->exit_prices.upper_secure_profit,
                 open_order_ptr_->max_profit * secured_profit_ratio_);

    std::cout << fmt.bold << fmt.yellow;
    printf("🚩 Awaiting hedge to close\n");
    std::cout << fmt.reset << std::endl;
  }

  return {
      .lower_secure_profit = lower_secure_profit,
      .max_loss = max_loss,
      .min_profit = min_profit,
      .position_target_movement = position_target_movement_,
      .upper_secure_profit = upper_secure_profit,
  };
}

#endif

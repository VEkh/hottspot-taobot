#ifndef ETRADE__TAO_BOT_build_exit_prices
#define ETRADE__TAO_BOT_build_exit_prices

/*
 * ETrade::TaoBot
 * closed_positions_stats_t
 * exit_prices_t
 * order_win_result_t
 * position_t
 */
#include "tao_bot.h"

#include "loss_to_recover.cpp"      // loss_to_recover
#include "secured_profit_ratio.cpp" // secured_profit_ratio
#include <algorithm>                // std::max
#include <math.h>                   // abs

ETrade::TaoBot::exit_prices_t ETrade::TaoBot::build_exit_prices() {
  const double max_loss_multiplier = 20.0;
  const double secured_profit_ratio_ = secured_profit_ratio();
  const double loss_to_recover_ = loss_to_recover();

  double max_loss = -1 * max_loss_multiplier * this->average_tick_price_delta;

  if (loss_to_recover_ < 0) {
    const double redemptive_max_loss =
        (1.05 * abs(loss_to_recover_)) / this->open_order.quantity;

    max_loss = -1 * std::max(redemptive_max_loss, abs(max_loss));
  }

  const double min_profit = abs(max_loss) / secured_profit_ratio_;

  const double secure_profit_lower =
      (secured_profit_ratio_ - 0.2) * this->open_order.max_profit;

  const double secure_profit_upper =
      secured_profit_ratio_ * this->open_order.max_profit;

  return {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .secure_profit_lower = secure_profit_lower,
      .secure_profit_upper = secure_profit_upper,
  };
}

#endif

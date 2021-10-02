#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "loss_to_recover.cpp"      // loss_to_recover
#include "secured_profit_ratio.cpp" // secured_profit_ratio
#include "tao_bot.h"                // Oanda::TaoBot
#include <algorithm>                // std::max std::min
#include <math.h>                   // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double loss_to_recover_ = loss_to_recover();
  const double max_loss_multiplier = 20.0;
  const double secured_profit_ratio_ = secured_profit_ratio();

  double max_loss = -1 * max_loss_multiplier * this->average_tick_price_delta;

  if (loss_to_recover_ < 0) {
    const double redemptive_max_loss =
        (1.05 * abs(loss_to_recover_)) / this->open_order.quantity;

    max_loss = -1 * std::min(redemptive_max_loss,
                             100.0 * this->average_tick_price_delta);
  }

  const double min_profit = abs(max_loss) / secured_profit_ratio_;

  const double secure_profit =
      std::max(this->exit_prices.secure_profit,
               secured_profit_ratio_ * this->open_order.max_profit);

  return {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .secure_profit = secure_profit,
  };
}

#endif

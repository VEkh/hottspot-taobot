#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "loss_to_recover.cpp" // loss_to_recover
#include "tao_bot.h"           // Oanda::TaoBot
#include <algorithm>           // std::max std::min
#include <math.h>              // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double loss_to_recover_ = loss_to_recover();
  const double secure_profit_ratio = 0.8;

  double max_loss =
      -1 * this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta;

  if (loss_to_recover_ < 0) {
    const double redemptive_max_loss =
        (1.05 * abs(loss_to_recover_)) / this->open_order.quantity;

    max_loss = -1 * redemptive_max_loss;
  }

  const double min_profit = abs(max_loss) * (1 / secure_profit_ratio);
  const double lower_secure_profit = min_profit * secure_profit_ratio;

  const double upper_secure_profit =
      std::max(this->exit_prices.upper_secure_profit,
               this->open_order.max_profit * secure_profit_ratio);

  return {
      .lower_secure_profit = lower_secure_profit,
      .max_loss = max_loss,
      .min_profit = min_profit,
      .upper_secure_profit = upper_secure_profit,
  };
}

#endif

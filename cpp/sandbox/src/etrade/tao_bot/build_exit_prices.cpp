#ifndef ETRADE__TAO_BOT_build_exit_prices
#define ETRADE__TAO_BOT_build_exit_prices

#include "loss_to_recover.cpp" // loss_to_recover
#include "tao_bot.h"           // ETrade::TaoBot
#include <algorithm>           // std::max std::min
#include <math.h>              // abs

ETrade::TaoBot::exit_prices_t ETrade::TaoBot::build_exit_prices() {
  const double max_loss =
      -this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta;

  const double min_profit = 1.25 * abs(max_loss);
  const double lower_secure_profit = min_profit * 0.8;

  const double upper_secure_profit = std::max(
      this->exit_prices.upper_secure_profit, this->open_order.max_profit * 0.8);

  return {
      .lower_secure_profit = lower_secure_profit,
      .max_loss = max_loss,
      .min_profit = min_profit,
      .upper_secure_profit = upper_secure_profit,
  };
}

#endif

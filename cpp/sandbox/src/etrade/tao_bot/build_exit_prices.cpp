#ifndef ETRADE__TAO_BOT_build_exit_prices
#define ETRADE__TAO_BOT_build_exit_prices

#include "loss_to_recover.cpp" // loss_to_recover
#include "tao_bot.h"           // ETrade::TaoBot
#include <algorithm>           // std::max std::min
#include <math.h>              // abs

ETrade::TaoBot::exit_prices_t ETrade::TaoBot::build_exit_prices() {
  const double loss_to_recover_ = loss_to_recover();
  const double max_loss_multiplier = this->MIN_TARGET_TICK_MOVEMENT;

  double max_loss = -1 * max_loss_multiplier * this->average_tick_price_delta;

  if (loss_to_recover_ < 0) {
    const double redemptive_max_loss =
        (1.05 * abs(loss_to_recover_)) / this->open_order.quantity;

    max_loss = -1 * redemptive_max_loss;
  }

  const double trailing_stop =
      std::min(abs(max_loss * 0.25),
               this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta);

  const double min_profit = abs(max_loss) + trailing_stop;

  const double secure_profit =
      std::max(this->exit_prices.secure_profit,
               this->open_order.max_profit - trailing_stop);

  return {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .secure_profit = secure_profit,
  };
}

#endif

#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "loss_to_recover.cpp"          // loss_to_recover
#include "position_target_movement.cpp" // position_target_movement
#include "secured_profit_ratio.cpp"     // secured_profit_ratio
#include "tao_bot.h"                    // Oanda::TaoBot
#include <algorithm>                    // std::max std::min
#include <math.h>                       // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  double max_loss = -position_target_movement();

  if (abs(loss_to_recover()) > 0 && abs(this->exit_prices.init_max_loss) > 0) {
    max_loss = this->exit_prices.init_max_loss;
  }

  const double init_max_loss = this->exit_prices.init_max_loss
                                   ? this->exit_prices.init_max_loss
                                   : max_loss;

  const double secured_profit_ratio_ = secured_profit_ratio();
  const double min_profit = (1 / secured_profit_ratio_) * abs(max_loss);
  const double lower_secure_profit = min_profit * secured_profit_ratio_;

  const double upper_secure_profit =
      std::max(this->exit_prices.upper_secure_profit,
               this->open_order.max_profit * secured_profit_ratio_);

  return {
      .init_max_loss = init_max_loss,
      .lower_secure_profit = lower_secure_profit,
      .max_loss = max_loss,
      .min_profit = min_profit,
      .upper_secure_profit = upper_secure_profit,
  };
}

#endif

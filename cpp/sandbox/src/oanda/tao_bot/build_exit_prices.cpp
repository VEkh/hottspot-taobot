#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "position_target_movement.cpp" // position_target_movement
#include "secured_profit_ratio.cpp"     // secured_profit_ratio
#include "tao_bot.h"                    // Oanda::TaoBot
#include <algorithm>                    // std::max std::min
#include <math.h>                       // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double max_loss = this->exit_prices.max_loss
                              ? this->exit_prices.max_loss
                              : -position_target_movement();

  const double secured_profit_ratio_ = secured_profit_ratio();
  const double min_profit = (1 / secured_profit_ratio_) * abs(max_loss);

  return {
      .max_loss = max_loss,
      .min_profit = min_profit,
  };
}

#endif

#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "dynamic_one_sec_variance.cpp" // dynamic_one_sec_variance
#include "tao_bot.h"                    // Oanda::TaoBot
#include <math.h>                       // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double one_sec_variance = dynamic_one_sec_variance();
  const int max_loss_coefficient = -80;

  const double max_loss = max_loss_coefficient * one_sec_variance;
  const double trailing_stop = 20 * one_sec_variance;
  const double min_profit = abs(10 * max_loss) + trailing_stop;

  const double trailing_stop_profit =
      this->open_order_ptr->max_profit - trailing_stop;

  exit_prices_t out = {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };

  return out;
}

#endif

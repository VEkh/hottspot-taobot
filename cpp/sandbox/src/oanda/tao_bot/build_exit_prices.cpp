#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Oanda::TaoBot
#include <math.h>    // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double static_one_sec_variance =
      this->price_movement.three_minute_one_second_variance.average;

  const int max_loss_coefficient = -80;

  const double max_loss = max_loss_coefficient * static_one_sec_variance;
  const double min_profit = abs(max_loss);

  const double trailing_stop_profit = this->open_order_ptr->max_profit * 0.5;

  exit_prices_t out = {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };

  return out;
}

#endif

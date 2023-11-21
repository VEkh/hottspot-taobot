#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Oanda::TaoBot
#include <math.h>    // abs

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;

  const double stop_profit_stop_loss_ratio = 2.5;
  const double trailing_stop_profit_ratio = 1 / 1.1;
  const int stop_loss_coefficient = -80;

  const double stop_loss = stop_loss_coefficient * static_one_sec_variance;
  const double stop_profit = abs(stop_profit_stop_loss_ratio * stop_loss);

  const double adjusted_stop_profit = stop_profit / trailing_stop_profit_ratio;

  const double trailing_stop_profit =
      this->open_order_ptr->max_profit * trailing_stop_profit_ratio;

  return {
      .stop_loss = stop_loss,
      .stop_profit = adjusted_stop_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };
}

#endif

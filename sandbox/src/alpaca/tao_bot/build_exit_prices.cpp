#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double trailing_stop_profit_ratio = 1 / 1.1;

  const double stop_loss_ratio = this->api_client.config.stop_loss_ratio;
  const double stop_profit_ratio =
      this->api_client.config.stop_profit_ratio
          ? this->api_client.config.stop_profit_ratio
          : 99999;

  const double max_loss = stop_loss_ratio * static_one_sec_variance;
  const double stop_profit = abs(stop_profit_ratio * max_loss);

  const double min_profit = stop_profit / trailing_stop_profit_ratio;

  const double trailing_stop_profit =
      this->open_order_ptr->max_profit * trailing_stop_profit_ratio;

  return {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };
}

#endif

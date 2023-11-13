#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "lib/utils/float.cpp" // ::utils::float_
#include "tao_bot.h"           // Alpaca::TaoBot
#include "volatility.cpp"      // volatility
#include <math.h>              // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double trailing_stop_profit_ratio = 1 / 1.1;

  double stop_loss_ratio = this->api_client.config.stop_loss_ratio;

  if (this->candle_predictor.should_predict() &&
      this->candle_predictor.config.stop_loss_ratio) {
    stop_loss_ratio = this->candle_predictor.config.stop_loss_ratio;
  }

  if (this->api_client.config.is_stop_loss_scaled) {
    const double stop_loss_multiplier = ::utils::float_::sigmoid({
        .decay_rate = 15.0,
        .max = 1,
        .min = 0.2,
        .x = volatility(),
        .x_shift = 0.75,
    });

    stop_loss_ratio = stop_loss_ratio * stop_loss_multiplier;
  }

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

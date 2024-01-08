#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "lib/utils/float.cpp" // ::utils::float_
#include "order_duration.cpp"  // order_duration
#include "tao_bot.h"           // Alpaca::TaoBot
#include "volatility.cpp"      // volatility
#include <math.h>              // abs, pow

// TODO: Decide
#include <algorithm> // std::max

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double trailing_stop_profit_ratio = 1 / 1.1;

  double stop_loss_ratio = this->api_client.config.stop_loss_ratio;
  double stop_profit_ratio = this->api_client.config.stop_profit_ratio;

  if (this->api_client.config.stop_loss_ratios[this->symbol]) {
    stop_loss_ratio = this->api_client.config.stop_loss_ratios[this->symbol];
  }

  if (this->api_client.config.should_use_alt_stop_loss) {
    stop_loss_ratio = this->api_client.config.alt_stop_loss_ratio;
  }

  // TODO: Decide
  if (this->api_client.config.is_stop_loss_decayed) {
    const double order_duration_ = order_duration(this->open_order_ptr);

    const double stop_loss_multiplier = ::utils::float_::sigmoid({
        .decay_rate = -1.0e-2,
        .max = 1,
        .min = 0.25,
        .x = order_duration_,
        .x_shift = 300,
    });

    stop_loss_ratio = stop_loss_ratio * stop_loss_multiplier;
  }

  if (this->api_client.config.should_expand_stop_loss &&
      this->performance.loss_streaks.longest) {
    // TODO: Decide
    int multiplier = 0;

    std::map<int, int>::iterator it =
        this->performance.loss_streaks.counts.begin();

    for (; it != this->performance.loss_streaks.counts.end(); it++) {
      multiplier += it->first * it->second;
    }

    stop_loss_ratio *= log(multiplier + 3);
    // stop_loss_ratio *= log(this->performance.loss_streaks.longest + 3); //
    // TODO: Decide
    // stop_loss_ratio *= log(this->performance.loss_streaks.current + 3); //
  }

  const double stop_loss = stop_loss_ratio * static_one_sec_variance;

  if (this->api_client.config.stop_profit_ratios[this->symbol]) {
    stop_profit_ratio =
        this->api_client.config.stop_profit_ratios[this->symbol];
  }

  if (this->api_client.config.is_stop_profit_decayed) {
    const double current_profit =
        std::max(10.0 * static_one_sec_variance, this->open_order_ptr->profit);

    const double multiplier =
        stop_loss ? 1.0 / abs(2.0 * current_profit / stop_loss) : 1.0;

    const double max_profit_duration =
        order_duration(this->open_order_ptr, "max_profit");

    const double x = multiplier * max_profit_duration;

    stop_profit_ratio = ::utils::float_::sigmoid({
        .decay_rate = -1e-2,
        .max = 20.0,
        .min = 1e-4,
        .x = x,
        .x_shift = 3 * 60,
    });
  }

  // TODO: Decide
  if (this->api_client.config.should_use_alt_stop_profit) {
    stop_profit_ratio = this->api_client.config.alt_stop_profit_ratio;
  }

  const double stop_profit = abs(stop_profit_ratio * stop_loss);

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

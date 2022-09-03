#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Oanda::TaoBot
#include <algorithm> // std::max std::min

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double one_sec_variance = std::max(
      this->price_movement.short_term_three_minute_one_second_variance.average,
      this->price_movement.three_minute_one_second_variance.average);

  const double exit_threshold = 40 * one_sec_variance;
  const double max_loss = -exit_threshold;
  const double min_profit = 1.05 * exit_threshold;
  const double trailing_stop = exit_threshold;

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

#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const price_movement_t price_movement = this->price_movement;

  const double one_sec_variance = std::max(
      price_movement.short_term_three_minute_one_second_variance.average,
      price_movement.three_minute_one_second_variance.average);

  const int win_to_loss_ratio = 1.5;
  const int loss_coefficient = 20;
  const int win_coefficient = win_to_loss_ratio * loss_coefficient;
  const double max_loss = loss_coefficient * one_sec_variance;
  const double min_profit = win_coefficient * one_sec_variance;

  const double trailing_stop_profit =
      std::max(min_profit, this->open_order_ptr->max_profit) - max_loss;

  exit_prices_t out = {
      .max_loss = -max_loss,
      .min_profit = min_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };

  return out;
}

#endif

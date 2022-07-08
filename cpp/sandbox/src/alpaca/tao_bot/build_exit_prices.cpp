#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max

Alpaca::TaoBot::exit_prices_t
Alpaca::TaoBot::build_exit_prices(const order_t *open_order_ptr_) {
  const double coefficients[] = {20.0, 30.0, 40.0};
  const double coefficient = coefficients[this->closed_positions.size() % 3];

  const price_movement_t price_movement =
      this->price_movements[open_order_ptr_->symbol];

  const double one_sec_variance = std::max(
      price_movement.short_term_three_minute_one_second_variance.average,
      price_movement.three_minute_one_second_variance.average);

  const double exit = coefficient * one_sec_variance;

  exit_prices_t out;
  out.max_loss = -exit;
  out.min_profit = exit;

  return out;
}

#endif

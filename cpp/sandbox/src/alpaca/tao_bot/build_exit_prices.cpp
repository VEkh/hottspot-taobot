#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "hedge_symbol.cpp" // hedge_symbol
#include "tao_bot.h"        // Alpaca::TaoBot, fmt

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices(
    order_t *open_order_ptr_,
    const order_t *opposite_close_order_ptr = nullptr) {
  const price_movement_t hedge_price_movement =
      this->price_movements[hedge_symbol()];

  const double hedge_one_sec_variance =
      hedge_price_movement.short_term_three_minute_one_second_variance.average
          ? hedge_price_movement.short_term_three_minute_one_second_variance
                .average
          : hedge_price_movement.three_minute_one_second_variance.average;

  const double target_profit =
      5.0 * hedge_one_sec_variance * this->hedge_open_order.quantity;

  exit_prices_t out;
  out.min_profit = target_profit;
  return out;
}

#endif

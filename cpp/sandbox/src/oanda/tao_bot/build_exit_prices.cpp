#ifndef OANDA__TAO_BOT_build_exit_prices
#define OANDA__TAO_BOT_build_exit_prices

#include "get_quote_price_range.cpp" // get_quote_price_range
#include "tao_bot.h"                 // Oanda::TaoBot
#include <algorithm>                 // std::min
#include <math.h>                    // abs
#include <utility>                   // std::pair

Oanda::TaoBot::exit_prices_t Oanda::TaoBot::build_exit_prices() {
  const double static_one_sec_variance =
      this->price_movement.three_minute_one_second_variance.average;

  const std::pair<double, double> quote_range = get_quote_price_range();
  const double price_range = quote_range.first - quote_range.second;
  const int max_loss_coefficient = -80;

  const double max_loss = std::min(
      max_loss_coefficient * static_one_sec_variance, price_range / -4.0);
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

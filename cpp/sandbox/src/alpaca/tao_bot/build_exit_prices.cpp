#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "dynamic_one_sec_variance.cpp" // dynamic_one_sec_variance
#include "get_quote_price_range.cpp"    // get_quote_price_range
#include "tao_bot.h"                    // Alpaca::TaoBot
#include <algorithm>                    // std::min
#include <math.h>                       // abs
#include <utility>                      // std::pair

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double one_sec_variance = dynamic_one_sec_variance();
  const double static_one_sec_variance =
      this->price_movement.three_minute_one_second_variance.average;

  const std::pair<double, double> quote_range = get_quote_price_range();
  const double price_range = quote_range.first - quote_range.second;
  const int max_loss_coefficient = -40;

  const double max_loss = std::min(
      max_loss_coefficient * static_one_sec_variance, price_range / -4.0);
  const double trailing_stop = 10 * one_sec_variance;
  const double min_profit = abs(10 * max_loss) + trailing_stop;

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

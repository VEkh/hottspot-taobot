#ifndef ETRADE__STOCK_BOTO_compute_min_profit_price_range_ratio
#define ETRADE__STOCK_BOTO_compute_min_profit_price_range_ratio

#include "stock_bot.h" // ETrade::StockBot
#include <cmath>       // exp

double ETrade::StockBot::compute_min_profit_price_range_ratio(
    const double buy_sell_ratio) {
  const double x = buy_sell_ratio;
  const double x_multiplier = 10;
  const double x_shift = -1.25;
  const double y_multiplier = 0.25;
  const double y_shift = 0.10;

  const double y =
      (y_multiplier / (1 + exp(-(x_multiplier * (x + x_shift))))) + y_shift;

  return y;
}

#endif

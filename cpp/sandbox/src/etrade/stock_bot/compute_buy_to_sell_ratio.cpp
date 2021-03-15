#if !defined ETRADE__STOCK_BOT_compute_buy_to_sell_ratio
#define ETRADE__STOCK_BOT_compute_buy_to_sell_ratio

#include "stock_bot.h" // ETrade::StockBot, sma_t
#include <math.h>      // INFINITY, abs

double ETrade::StockBot::compute_buy_to_sell_ratio(
    const sma_t &simple_moving_average) {
  if (!simple_moving_average.buy_delta && !simple_moving_average.sell_delta) {
    return 0;
  }

  return abs(simple_moving_average.buy_delta /
             simple_moving_average.sell_delta);
}

#endif

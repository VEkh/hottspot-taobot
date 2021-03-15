#if !defined ETRADE__STOCK_BOT_compute_sell_to_buy_ratio
#define ETRADE__STOCK_BOT_compute_sell_to_buy_ratio

#include "compute_buy_to_sell_ratio.cpp" // compute_buy_to_sell_ratio
#include "stock_bot.h"                   // ETrade::StockBot, sma_t

double ETrade::StockBot::compute_sell_to_buy_ratio(
    const sma_t &simple_moving_average) {
  const double buy_to_sell_ratio =
      compute_buy_to_sell_ratio(simple_moving_average);

  return buy_to_sell_ratio ? 1.0 / buy_to_sell_ratio : 0;
}

#endif

#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

/*
 * ETrade::StockBot
 * quote_t
 */
#include "stock_bot.h"

#include "compute_moving_buy_sell_ratio_average.cpp" // compute_moving_buy_sell_ratio_average
#include "lib/utils/integer.cpp"                     // utils::integer_
#include <iostream>                                  // std::cout, std::endl
#include <math.h>                                    // abs

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const int average_period_seconds = 30;
  const double average_buy_sell_ratio =
      compute_moving_buy_sell_ratio_average(average_period_seconds);
  const double average_sell_buy_ratio =
      average_buy_sell_ratio ? 1.0 / average_buy_sell_ratio : 0;
  const double entry_threshold = 1.0;

  std::cout << fmt.cyan;
  std::cout << "Average Buy-Sell ("
            << utils::integer_::seconds_to_clock(average_period_seconds)
            << ") Δ: " << average_buy_sell_ratio << std::endl;
  std::cout << "Average Sell-Buy ("
            << utils::integer_::seconds_to_clock(average_period_seconds)
            << ") Δ: " << average_buy_sell_ratio << std::endl;
  std::cout << fmt.reset << std::endl;

  if (average_buy_sell_ratio >= entry_threshold ||
      average_sell_buy_ratio >= entry_threshold) {
    this->is_long_position = average_buy_sell_ratio >= entry_threshold;
    return true;
  }

  return false;
}

#endif

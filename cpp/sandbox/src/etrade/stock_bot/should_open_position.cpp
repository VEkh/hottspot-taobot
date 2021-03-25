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
#include <vector>                                    // std::vector

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  int long_period_seconds = 5 * 60;
  std::vector<int> periods = {long_period_seconds};

  std::map<int, std::map<const char *, double>> average_buy_sell_ratios =
      compute_moving_buy_sell_ratio_average(periods);

  const double long_average_buy_sell_ratio =
      average_buy_sell_ratios[long_period_seconds]["buy"];
  const double long_average_sell_buy_ratio =
      average_buy_sell_ratios[long_period_seconds]["sell"];

  const sma_t simple_moving_average = this->quotes.back().simple_moving_average;
  const double buy_sell_ratio = simple_moving_average.buy_sell_ratio;
  const double sell_buy_ratio = simple_moving_average.sell_buy_ratio;

  const double short_entry_threshold = 1.4;
  const double long_entry_threshold = 1.0;

  std::cout << fmt.cyan;

  for (int period : periods) {
    std::cout << "Average Buy-Sell ("
              << utils::integer_::seconds_to_clock(period)
              << ") Δ: " << average_buy_sell_ratios[period]["buy"] << std::endl;
    std::cout << "Average Sell-Buy ("
              << utils::integer_::seconds_to_clock(period)
              << ") Δ: " << average_buy_sell_ratios[period]["sell"]
              << std::endl;
  }

  std::cout << fmt.reset << std::endl;

  if (buy_sell_ratio >= short_entry_threshold &&
      long_average_buy_sell_ratio >= long_entry_threshold) {
    this->is_long_position = true;
    return true;
  }

  if (sell_buy_ratio >= short_entry_threshold &&
      long_average_sell_buy_ratio >= long_entry_threshold) {
    this->is_long_position = false;
    return true;
  }

  return false;
}

#endif

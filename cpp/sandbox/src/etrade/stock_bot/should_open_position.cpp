#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

/*
 * ETrade::StockBot
 * quote_t
 */
#include "stock_bot.h"

#include "compute_door_moving_average_period.cpp" // compute_door_moving_average_period
#include "compute_moving_buy_sell_ratio_average.cpp" // compute_moving_buy_sell_ratio_average
#include "lib/utils/integer.cpp"                     // utils::integer_
#include <iostream>                                  // std::cout, std::endl
#include <math.h>                                    // abs
#include <vector>                                    // std::vector

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  int period_seconds_1 = 1 * 60;
  int period_seconds_2 = 2 * 60;
  int period_seconds_5 = 5 * 60;

  std::vector<int> periods = {
      period_seconds_1,
      period_seconds_2,
      period_seconds_5,
  };

  std::map<int, std::map<const char *, double>> average_buy_sell_ratios =
      compute_moving_buy_sell_ratio_average(periods);

  const double average_buy_sell_ratio_1 =
      average_buy_sell_ratios[period_seconds_1]["buy"];
  const double average_sell_buy_ratio_1 =
      average_buy_sell_ratios[period_seconds_1]["sell"];

  const double average_buy_sell_ratio_5 =
      average_buy_sell_ratios[period_seconds_5]["buy"];
  const double average_sell_buy_ratio_5 =
      average_buy_sell_ratios[period_seconds_5]["sell"];

  const double entry_threshold_1 = 1.2;
  const double entry_threshold_5 = 1.0;

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

  if (average_buy_sell_ratio_1 >= entry_threshold_1 &&
      average_buy_sell_ratio_5 >= entry_threshold_5) {
    this->is_long_position = true;
    return true;
  }

  if (average_sell_buy_ratio_1 >= entry_threshold_1 &&
      average_sell_buy_ratio_5 >= entry_threshold_5) {
    this->is_long_position = false;
    return true;
  }

  return false;
}

#endif

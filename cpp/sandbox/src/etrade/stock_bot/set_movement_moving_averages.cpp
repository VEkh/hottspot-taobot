#if !defined ETRADE__STOCK_BOT_set_movement_moving_averages
#define ETRADE__STOCK_BOT_set_movement_moving_averages

#include "compute_moving_buy_sell_ratio_average.cpp" // compute_moving_buy_sell_ratio_average
#include "lib/utils/integer.cpp"                     // utils::integer_
#include "stock_bot.h"                               // ETrade::StockBot
#include <iostream>                                  // std::cout, std::endl
#include <vector>                                    // std::vector

void ETrade::StockBot::set_movement_moving_averages() {
  int long_period_seconds = 5 * 60;
  int short_period_seconds = 0.5 * 60;
  std::vector<int> periods = {short_period_seconds, long_period_seconds};

  std::map<int, std::map<const char *, double>> average_buy_sell_ratios =
      compute_moving_buy_sell_ratio_average(periods);

  this->long_average_buy_sell_ratio =
      average_buy_sell_ratios[long_period_seconds]["buy"];
  this->long_average_sell_buy_ratio =
      average_buy_sell_ratios[long_period_seconds]["sell"];

  this->short_average_buy_sell_ratio =
      average_buy_sell_ratios[short_period_seconds]["buy"];
  this->short_average_sell_buy_ratio =
      average_buy_sell_ratios[short_period_seconds]["sell"];

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
}

#endif

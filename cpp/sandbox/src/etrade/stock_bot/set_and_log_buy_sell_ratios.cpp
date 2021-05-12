#if !defined ETRADE__STOCK_BOT_set_and_log_buy_sell_ratios
#define ETRADE__STOCK_BOT_set_and_log_buy_sell_ratios

/*
 * ETrade::StockBot
 * fmt
 * quotes
 */
#include "stock_bot.h"

#include "compute_moving_buy_sell_ratio_average.cpp" // compute_moving_buy_sell_ratio_average
#include "lib/formatted.cpp"                         // Formatted
#include "lib/utils/integer.cpp"                     // utils::integer_
#include <iomanip>                                   // std::setprecision
#include <iostream> // std::cout, std::endl, std::fixed
#include <vector>   // std::vector

void ETrade::StockBot::set_and_log_buy_sell_ratios() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = this->quotes.size();

  if (!ticks) {
    return;
  }

  int long_period_seconds = 5 * 60;
  int short_period_seconds = 2.5 * 60;
  std::vector<int> moving_average_periods = {
      short_period_seconds,
      long_period_seconds,
  };

  std::map<int, std::map<const char *, double>> average_buy_sell_ratios =
      compute_moving_buy_sell_ratio_average(moving_average_periods);

  this->long_average_buy_sell_ratio =
      average_buy_sell_ratios[long_period_seconds]["buy"];
  this->long_average_sell_buy_ratio =
      average_buy_sell_ratios[long_period_seconds]["sell"];

  this->short_average_buy_sell_ratio =
      average_buy_sell_ratios[short_period_seconds]["buy"];
  this->short_average_sell_buy_ratio =
      average_buy_sell_ratios[short_period_seconds]["sell"];

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << fmt.bold << fmt.underline << fmt.cyan;
  std::cout << "Buy-Sell Ratios" << std::endl;
  std::cout << fmt.reset;
  std::cout << fmt.bold << fmt.cyan;

  for (int period : moving_average_periods) {
    std::cout << "Avg. Buy Δ / Sell Δ ("
              << utils::integer_::seconds_to_clock(period)
              << "): " << average_buy_sell_ratios[period]["buy"] << std::endl;
    std::cout << "Avg. Sell Δ / Buy Δ ("
              << utils::integer_::seconds_to_clock(period)
              << "): " << average_buy_sell_ratios[period]["sell"] << std::endl;
  }

  std::cout << fmt.reset << std::endl;
}

#endif

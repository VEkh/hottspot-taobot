#if !defined ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * fmt
 * order_status_t
 * quote_t
 * sma_t
 */
#include "stock_bot.h"

#include "compute_moving_buy_sell_ratio_average.cpp" // compute_moving_buy_sell_ratio_average
#include "lib/utils/integer.cpp"                     // utils::integer_
#include <iostream>                                  // std::cout, std::endl
#include <math.h>                                    // abs

bool ETrade::StockBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
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

  const double exit_threshold = 1.0;
  const double profit_percentage =
      100 * (this->open_order.profit / this->open_order.execution_price);
  const double secure_profit_percentage = 0.05;

  if (abs(profit_percentage) >= 0.15) {
    return true;
  }

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

  return false;
}

#endif

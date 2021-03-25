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

bool ETrade::StockBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
    return false;
  }

  const double profit_percentage =
      100 * (this->open_order.profit / this->open_order.execution_price);

  if (profit_percentage >= 0.2) {
    return true;
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

  const sma_t simple_moving_average = this->quotes.back().simple_moving_average;
  const double buy_sell_ratio = simple_moving_average.buy_sell_ratio;
  const double sell_buy_ratio = simple_moving_average.sell_buy_ratio;

  const double exit_threshold = 1.0;

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

  if (this->is_long_position) {
    return buy_sell_ratio <= exit_threshold;
  } else if (!this->is_long_position) {
    return sell_buy_ratio <= exit_threshold;
  }

  return false;
}

#endif

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

  if (profit_percentage >= 0.25) {
    return true;
  }

  const int average_period_seconds = 60;
  const double average_buy_sell_ratio =
      compute_moving_buy_sell_ratio_average(average_period_seconds);
  const double average_sell_buy_ratio =
      average_buy_sell_ratio ? 1.0 / average_buy_sell_ratio : 0;
  const double exit_threshold = 1.0;

  std::cout << fmt.cyan;
  std::cout << "Average Buy-Sell ("
            << utils::integer_::seconds_to_clock(average_period_seconds)
            << ") Δ: " << average_buy_sell_ratio << std::endl;
  std::cout << "Average Sell-Buy ("
            << utils::integer_::seconds_to_clock(average_period_seconds)
            << ") Δ: " << average_buy_sell_ratio << std::endl;
  std::cout << fmt.reset << std::endl;

  if (this->is_long_position) {
    return average_buy_sell_ratio <= exit_threshold;
  } else if (!this->is_long_position) {
    return average_buy_sell_ratio >= exit_threshold;
  }

  return false;
}

#endif

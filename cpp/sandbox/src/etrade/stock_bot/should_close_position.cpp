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

#include "compute_door_moving_average_period.cpp" // compute_door_moving_average_period
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

  const int average_period_seconds_1 = 1 * 60;
  const double average_buy_sell_ratio_1 =
      compute_moving_buy_sell_ratio_average(average_period_seconds_1);
  const double average_sell_buy_ratio_1 =
      average_buy_sell_ratio_1 ? 1.0 / average_buy_sell_ratio_1 : 0;

  const int average_period_seconds_5 = 5 * 60;
  const double average_buy_sell_ratio_5 =
      compute_moving_buy_sell_ratio_average(average_period_seconds_5);
  const double average_sell_buy_ratio_5 =
      average_buy_sell_ratio_5 ? 1.0 / average_buy_sell_ratio_5 : 0;

  const double exit_threshold_1 = 1.2;
  const double profit_exit_threshold_1 = 1.1;
  const double exit_threshold_5 = 1.0;

  std::cout << fmt.cyan;
  std::cout << "Average Buy-Sell ("
            << utils::integer_::seconds_to_clock(average_period_seconds_1)
            << ") Δ: " << average_buy_sell_ratio_1 << std::endl;
  std::cout << "Average Sell-Buy ("
            << utils::integer_::seconds_to_clock(average_period_seconds_1)
            << ") Δ: " << average_sell_buy_ratio_1 << std::endl;
  std::cout << "Average Buy-Sell ("
            << utils::integer_::seconds_to_clock(average_period_seconds_5)
            << ") Δ: " << average_buy_sell_ratio_5 << std::endl;
  std::cout << "Average Sell-Buy ("
            << utils::integer_::seconds_to_clock(average_period_seconds_5)
            << ") Δ: " << average_sell_buy_ratio_5 << std::endl;
  std::cout << fmt.reset << std::endl;

  if (this->is_long_position) {
    if (average_buy_sell_ratio_5 <= exit_threshold_5) {
      return true;
    }

    if (this->open_order.profit > 0 &&
        average_buy_sell_ratio_1 <= profit_exit_threshold_1) {
      return true;
    }
  } else if (!this->is_long_position) {
    if (average_sell_buy_ratio_5 <= exit_threshold_5) {
      return true;
    }

    if (this->open_order.profit > 0 &&
        average_sell_buy_ratio_1 <= profit_exit_threshold_1) {
      return true;
    }
  }

  return false;
}

#endif

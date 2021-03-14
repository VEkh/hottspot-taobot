#if !defined ETRADE__STOCK_BOT_log_open_position
#define ETRADE__STOCK_BOT_log_open_position

/*
 * ETrade::StockBot
 * fmt
 */
#include "stock_bot.h"

#include "etrade/constants.cpp" // ETrade::constants
#include "is_long_side.cpp"     // is_long_side
#include "lib/formatted.cpp"    // Formatted
#include "lib/utils/float.cpp"  // utils::float
#include <iomanip>              // std::setprecision
#include <iostream>             // std::cout, std::endl, std::fixed

void ETrade::StockBot::log_open_position() {
  if (!this->open_order_ptr && !this->close_order_ptr) {
    std::cout << fmt.bold << fmt.cyan;
    std::cout << "💀 No Open Positions." << std::endl << std::endl;
    std::cout << fmt.reset;

    return;
  }

  const bool is_long_side_ = is_long_side(this->open_order);
  const char *side = is_long_side_ ? "BUY" : "SELL_SHORT";
  Formatted::Stream log_color = is_long_side_ ? fmt.green : fmt.red;

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << fmt.bold << fmt.underline << log_color;
  std::cout << ETrade::constants::ORDER_ACTIONS[this->open_order.action]
            << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.bold << log_color;
  std::cout << "Open   => Execution: " << this->open_order.execution_price;
  std::cout << " • Profit: " << this->open_order.profit << std::endl;
  std::cout << "Close  => Execution: " << this->close_order.execution_price;
  std::cout << " • Profit: " << this->close_order.profit << std::endl;
  std::cout << "Status => Open: "
            << ETrade::constants::ORDER_STATUSES[this->open_order.status];
  std::cout << " • Close: "
            << ETrade::constants::ORDER_STATUSES[this->close_order.status]
            << std::endl;
  std::cout << fmt.reset << std::endl;
}

#endif

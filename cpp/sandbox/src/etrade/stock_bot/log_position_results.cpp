#ifndef ETRADE__STOCK_BOT_log_position_results
#define ETRADE__STOCK_BOT_log_position_results

/*
 * ETrade::StockBot
 * fmt
 * order_status_t
 * position_result_t
 * position_t
 */
#include "stock_bot.h"

#include "etrade/constants.cpp"    // ETrade::constants
#include "log_position.cpp"        // log_position
#include "set_execution_price.cpp" // set_execution_price
#include "set_profit.cpp"          // set_profit
#include <iostream>                // std::cout, std::endl

void ETrade::StockBot::log_position_results() {
  if (!this->close_order_ptr || !this->open_order_ptr) {
    return;
  }

  if (this->close_order.status != order_status_t::ORDER_EXECUTED) {
    return;
  }

  const char *order_action =
      ETrade::constants::ORDER_ACTIONS[this->open_order.action];

  set_execution_price(this->close_order_ptr);
  set_profit(this->close_order_ptr, this->open_order_ptr);

  if (this->close_order.profit > 0) {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << "🎉 " << order_action << ": Closed order at a gain."
              << std::endl;
  } else if (this->close_order.profit == 0) {
    std::cout << fmt.bold << fmt.yellow << std::endl;
    std::cout << "😅 " << order_action << ": Closed order at no loss, no gain."
              << std::endl;
  } else {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout << "😭 " << order_action
              << ": Closed order at a loss. Better luck next time!"
              << std::endl;
  }

  std::cout << fmt.reset << std::endl;

  log_position();
}

#endif

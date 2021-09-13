#ifndef ETRADE__TAO_BOT_log_order_win_results
#define ETRADE__TAO_BOT_log_order_win_results

/*
 * ETrade::TaoBot
 * fmt
 * order_status_t
 * order_win_result_t
 * position_t
 */
#include "tao_bot.h"

#include "etrade/constants.cpp"    // ETrade::constants
#include "log_position.cpp"        // log_position
#include "order_win_result.cpp"    // order_win_result
#include "set_execution_price.cpp" // set_execution_price
#include "set_profit.cpp"          // set_profit
#include <iostream>                // std::cout, std::endl

void ETrade::TaoBot::log_position_results() {
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

  order_win_result_t win_result = order_win_result(this->close_order_ptr);

  switch (win_result) {
  case order_win_result_t::LOSS: {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout << "😭 " << order_action
              << ": Closed order at a loss. Better luck next time!"
              << std::endl;

    break;
  }
  case order_win_result_t::TIE: {
    std::cout << fmt.bold << fmt.yellow << std::endl;
    std::cout << "😅 " << order_action << ": Closed order at no loss, no gain."
              << std::endl;

    break;
  }
  case order_win_result_t::WIN: {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << "🎉 " << order_action << ": Closed order at a gain."
              << std::endl;

    break;
  }
  }

  std::cout << fmt.reset << std::endl;

  log_position();
}

#endif

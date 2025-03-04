#ifndef OANDA__TAO_BOT_log_order_win_results
#define OANDA__TAO_BOT_log_order_win_results

/*
 * Oanda::TaoBot
 * fmt
 * order_status_t
 * order_win_result_t
 */
#include "tao_bot.h"

#include "lib/utils/string.cpp" // ::utils::string
#include "log_position.cpp"     // log_position
#include "oanda/constants.cpp"  // Oanda::constants
#include "order_win_result.cpp" // order_win_result
#include <iostream>             // std::cout, std::endl
#include <stdio.h>              // printf

void Oanda::TaoBot::log_position_results() {
  if (!(this->close_order_ptr && this->open_order_ptr)) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  const std::string order_action = ::utils::string::upcase(
      Oanda::constants::ORDER_ACTIONS[this->open_order.action]);

  order_win_result_t win_result = order_win_result({
      .close_order = this->close_order,
      .open_order = this->open_order,
  });

  switch (win_result) {
  case order_win_result_t::LOSS: {
    std::cout << fmt.bold << fmt.red << std::endl;
    printf("😭 %s: Closed order at a loss. Better luck next time!",
           order_action.c_str());
    std::cout << std::endl;

    break;
  }
  case order_win_result_t::TIE: {
    std::cout << fmt.bold << fmt.yellow << std::endl;
    printf("😅 %s: Closed order at no loss, no gain.", order_action.c_str());
    std::cout << std::endl;

    break;
  }
  case order_win_result_t::WIN: {
    std::cout << fmt.bold << fmt.green << std::endl;
    printf("🎉 %s: Closed order at a gain.", order_action.c_str());
    std::cout << std::endl;

    break;
  }
  }

  std::cout << fmt.reset << std::endl;

  log_position();
}

#endif

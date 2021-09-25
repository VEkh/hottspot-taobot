#ifndef ETRADE__TAO_BOT_close_position
#define ETRADE__TAO_BOT_close_position

/*
 * ETrade::TaoBot
 * api_client
 * fmt
 */
#include "tao_bot.h"

#include "etrade/constants.cpp"      // ETrade::constants
#include "set_profit.cpp"            // set_profit
#include "should_close_position.cpp" // should_close_position
#include <iostream>                  // std::cout, std::endl

void ETrade::TaoBot::close_position() {
  if (!should_close_position()) {
    return;
  }

  const char *order_action =
      ETrade::constants::ORDER_ACTIONS[this->open_order.action];

  const char *log_icon = this->ICONS[order_action];

  api_client.place_order(this->close_order_ptr);

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << log_icon << " " << order_action << ": Placed closing order."
            << std::endl;
  std::cout << fmt.reset;
}

#endif

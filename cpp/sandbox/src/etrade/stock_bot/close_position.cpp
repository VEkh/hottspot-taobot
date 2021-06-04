#if !defined ETRADE__STOCK_BOT_close_position
#define ETRADE__STOCK_BOT_close_position

/*
 * ETrade::StockBot
 * etrade_client
 * fmt
 */
#include "stock_bot.h"

#include "etrade/constants.cpp"      // ETrade::constants
#include "set_profit.cpp"            // set_profit
#include "should_close_position.cpp" // should_close_position
#include <iostream>                  // std::cout, std::endl

void ETrade::StockBot::close_position() {
  if (!should_close_position()) {
    return;
  }

  const char *order_action =
      ETrade::constants::ORDER_ACTIONS[this->open_order.action];

  const char *log_icon = this->ICONS[order_action];

  etrade_client.place_order(this->close_order_ptr);

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << log_icon << " " << order_action << ": Placed closing order."
            << std::endl;
  std::cout << fmt.reset;
}

#endif

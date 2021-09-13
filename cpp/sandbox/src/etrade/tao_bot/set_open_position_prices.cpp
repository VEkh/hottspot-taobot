#ifndef ETRADE__TAO_BOT_set_open_position_prices
#define ETRADE__TAO_BOT_set_open_position_prices

#include "etrade/utils.cpp"        // ETrade::constants
#include "set_execution_price.cpp" // set_execution_price
#include "set_profit.cpp"          // set_profit
#include "tao_bot.h"             // ETrade::TaoBot, fmt, order_status_t
#include <iostream>                // std::cout, std::endl

void ETrade::TaoBot::set_open_position_prices() {
  if (!this->open_order_ptr ||
      this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return;
  }

  const char *order_action =
      ETrade::constants::ORDER_ACTIONS[this->open_order.action];

  const char *log_icon = this->ICONS[order_action];

  if (!this->open_order.execution_price) {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << log_icon << " " << order_action << ": Executed open order.\n"
              << std::endl;
    std::cout << fmt.reset;

    set_execution_price(this->open_order_ptr);
  }

  set_profit(this->open_order_ptr);
}

#endif

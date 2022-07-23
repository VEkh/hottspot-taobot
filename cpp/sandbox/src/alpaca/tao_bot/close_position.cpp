#ifndef ALPACA__TAO_BOT_close_position
#define ALPACA__TAO_BOT_close_position

#include "alpaca/constants.cpp"      // Alpaca::constants
#include "lib/utils/string.cpp"      // ::utils::string
#include "should_close_position.cpp" // should_close_position
#include "tao_bot.h"                 // Alpaca::TaoBot, fmt, order_t
#include <iostream>                  // std::cout, std::endl
#include <stdio.h>                   // printf

void Alpaca::TaoBot::close_position(const double limit_price = 0.00,
                                    const bool force = false) {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  if (!force &&
      !should_close_position(this->close_order_ptr, this->open_order_ptr)) {
    return;
  }

  const char *order_action =
      Alpaca::constants::ORDER_ACTIONS[this->open_order_ptr->action];

  const char *log_icon = this->ICONS[order_action];

  if (limit_price) {
    this->close_order_ptr->limit_price = limit_price;
    this->close_order_ptr->type = order_type_t::LIMIT;
  }

  this->api_client.place_order(this->close_order_ptr);

  std::cout << fmt.bold << fmt.cyan << std::endl;
  printf("%s %s: Placed closing order.\n", log_icon,
         ::utils::string::upcase(order_action).c_str());
  std::cout << fmt.reset;
}

#endif

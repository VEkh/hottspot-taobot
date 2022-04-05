#ifndef ALPACA__TAO_BOT_close_position
#define ALPACA__TAO_BOT_close_position

#include "alpaca/constants.cpp"      // Alpaca::constants
#include "lib/utils/string.cpp"      // ::utils::string
#include "should_close_position.cpp" // should_close_position
#include "tao_bot.h"                 // Alpaca::TaoBot, fmt, order_t
#include <iostream>                  // std::cout, std::endl
#include <stdio.h>                   // printf

void Alpaca::TaoBot::close_position(Alpaca::Client &api_client_ref,
                                    order_t *close_order_ptr_,
                                    order_t *open_order_ptr_,
                                    const bool force = false) {
  if (!open_order_ptr_ || !close_order_ptr_) {
    return;
  }

  if (!force && !should_close_position(close_order_ptr_, open_order_ptr_)) {
    return;
  }

  const char *order_action =
      Alpaca::constants::ORDER_ACTIONS[open_order_ptr_->action];

  const char *log_icon = this->ICONS[order_action];

  api_client_ref.place_order(close_order_ptr_);

  std::cout << fmt.bold << fmt.cyan << std::endl;
  printf("%s %s: Placed closing order.\n", log_icon,
         ::utils::string::upcase(order_action).c_str());
  std::cout << fmt.reset;
}

#endif

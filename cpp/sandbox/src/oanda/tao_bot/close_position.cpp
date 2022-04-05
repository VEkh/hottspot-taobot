#ifndef OANDA__TAO_BOT_close_position
#define OANDA__TAO_BOT_close_position

#include "oanda/constants.cpp"       // Oanda::constants
#include "should_close_position.cpp" // should_close_position
#include "tao_bot.h"                 // Oanda::TaoBot, fmt
#include <iostream>                  // std::cout, std::endl
#include <stdio.h>                   // printf

void Oanda::TaoBot::close_position() {
  if (!should_close_position()) {
    return;
  }

  puts("OANDA__TAO_BOT_close_position");
  std::cout << std::flush;

  const char *order_action =
      Oanda::constants::ORDER_ACTIONS[this->open_order.action];

  const char *log_icon = this->ICONS[order_action];

  this->api_client.place_order(this->close_order_ptr);

  std::cout << fmt.bold << fmt.cyan << std::endl;
  printf("%s %s: Placed closing order.\n", log_icon, order_action);
  std::cout << fmt.reset;
}

#endif

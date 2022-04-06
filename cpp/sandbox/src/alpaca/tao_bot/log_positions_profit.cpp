#ifndef ALPACA__TAO_BOT_log_positions_profit
#define ALPACA__TAO_BOT_log_positions_profit

#include "lib/formatted.cpp"        // Formatted
#include "open_position_profit.cpp" // open_position_profit
#include "tao_bot.h"                // Alpaca::TaoBot, fmt
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf

void Alpaca::TaoBot::log_positions_profit() {
  const double profit =
      open_position_profit(this->open_order_ptr, this->hedge_open_order_ptr);

  Formatted::Stream log_color = profit >= 0 ? fmt.green : fmt.red;

  std::cout << fmt.bold << log_color;
  printf("Position Profit: %.2f\n", profit);
  std::cout << fmt.reset << std::endl;
}
#endif

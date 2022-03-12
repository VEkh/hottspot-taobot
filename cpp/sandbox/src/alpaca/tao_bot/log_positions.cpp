#ifndef ALPACA__TAO_BOT_log_positions
#define ALPACA__TAO_BOT_log_positions

#include "is_position_closed.cpp" // is_position_closed
#include "log_position.cpp"       // log_position
#include "tao_bot.h"              // Alpaca::TaoBot, fmt
#include <iostream>               // std::cout, std::endl
#include <stdio.h>                // puts

void Alpaca::TaoBot::log_positions() {
  if (is_position_closed()) {
    std::cout << fmt.bold << fmt.cyan;
    puts("💀 No Open Positions.\n");
    std::cout << fmt.reset;

    return;
  }

  log_position(this->close_order_ptr, this->open_order_ptr);

  if (is_hedging()) {
    log_position(this->hedge_close_order_ptr, this->hedge_open_order_ptr,
                 " (Hedge)");
  }
}
#endif

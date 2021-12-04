#ifndef ETRADE__TAO_BOT_set_next_trade_direction
#define ETRADE__TAO_BOT_set_next_trade_direction

#include "set_next_trade_direction.cpp" // set_next_trade_direction
#include "iostream"                     // std::count
#include "stdio.h"                      // puts
#include "tao_bot.h"                    // ETrade::TaoBot, fmt

void ETrade::TaoBot::set_next_trade_direction() {
  const int loss_streak = this->performance.loss_streaks.current;

  if (loss_streak > 3 && loss_streak % 2 == 0) {
    std::cout << fmt.bold << fmt.yellow;
    puts("\n⏩ Not reversing the next trade direction.");
    std::cout << fmt.reset;

    return;
  }

  this->is_long_position = !this->is_long_position;
}

#endif

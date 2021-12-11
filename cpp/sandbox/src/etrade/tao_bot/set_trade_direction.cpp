#ifndef ETRADE__TAO_BOT_set_trade_direction
#define ETRADE__TAO_BOT_set_trade_direction

#include "set_trade_direction.cpp" // set_trade_direction
#include "flip_coin.cpp"           // flip_coin
#include "iostream"                // std::count
#include "stdio.h"                 // puts
#include "tao_bot.h"               // ETrade::TaoBot, fmt

void ETrade::TaoBot::set_trade_direction() {
  if (!this->closed_positions.size()) {
    this->is_long_position = flip_coin();

    return;
  }

  const int loss_streak = this->performance.loss_streaks.current;

  if (loss_streak > 2) {
    const bool direction = (loss_streak / 3) % 2;

    std::cout << fmt.bold << fmt.yellow << std::endl;
    printf("%s Setting consecutive direction to %s\n",
           direction ? "👆🏾" : "👇🏾", direction ? "BUY" : "SELL");
    std::cout << fmt.reset;

    this->is_long_position = direction;

    return;
  }

  this->is_long_position = !this->is_long_position;
}

#endif

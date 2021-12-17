#ifndef ETRADE__TAO_BOT_set_trade_direction
#define ETRADE__TAO_BOT_set_trade_direction

#include "flip_coin.cpp" // flip_coin
#include "tao_bot.h"     // ETrade::TaoBot, fmt

void ETrade::TaoBot::set_trade_direction() {
  if (!this->closed_positions.size()) {
    this->is_long_position = flip_coin();

    return;
  }

  this->is_long_position = !this->is_long_position;
}

#endif

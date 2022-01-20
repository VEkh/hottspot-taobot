#ifndef ALPACA__TAO_BOT_set_trade_direction
#define ALPACA__TAO_BOT_set_trade_direction

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::set_trade_direction() {
  this->is_long_position = ((this->closed_positions.size() / 3) % 2) == 0;
}

#endif

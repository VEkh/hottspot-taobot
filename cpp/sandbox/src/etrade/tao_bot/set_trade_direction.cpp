#ifndef ETRADE__TAO_BOT_set_trade_direction
#define ETRADE__TAO_BOT_set_trade_direction

#include "tao_bot.h" // ETrade::TaoBot, fmt

void ETrade::TaoBot::set_trade_direction() {
  this->is_long_position = !(bool)this->is_long_position;
}

#endif

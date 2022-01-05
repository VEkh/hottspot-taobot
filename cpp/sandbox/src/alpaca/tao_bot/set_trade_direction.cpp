#ifndef ALPACA__TAO_BOT_set_trade_direction
#define ALPACA__TAO_BOT_set_trade_direction

#include "tao_bot.h" // Alpaca::TaoBot, fmt

void Alpaca::TaoBot::set_trade_direction() {
  this->is_long_position = !(bool)this->is_long_position;
}

#endif

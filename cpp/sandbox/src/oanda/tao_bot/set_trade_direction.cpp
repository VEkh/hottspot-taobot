#ifndef OANDA__TAO_BOT_set_trade_direction
#define OANDA__TAO_BOT_set_trade_direction

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::set_trade_direction() {
  this->is_long_position = ((this->closed_positions.size() / 3) % 2) == 0;
}

#endif

#ifndef ALPACA__TAO_BOT_does_position_exist
#define ALPACA__TAO_BOT_does_position_exist

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::does_position_exist() {
  return !this->closed_positions.empty() || !!this->open_order_ptr;
}

#endif

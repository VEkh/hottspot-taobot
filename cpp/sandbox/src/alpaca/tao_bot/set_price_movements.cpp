#ifndef ALPACA__TAO_BOT_set_price_movements
#define ALPACA__TAO_BOT_set_price_movements

#include "set_price_movement.cpp"   // set_price_movement
#include "tao_bot.h"                // Alpaca::TaoBot
#include "write_price_movement.cpp" // write_price_movement

void Alpaca::TaoBot::set_price_movements() {
  set_price_movement(this->symbol);
  write_price_movement(this->symbol, this->price_movements[this->symbol]);
}

#endif

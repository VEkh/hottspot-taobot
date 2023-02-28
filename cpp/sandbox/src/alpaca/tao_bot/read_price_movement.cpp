#ifndef ALPACA__TAO_BOT_read_price_movement
#define ALPACA__TAO_BOT_read_price_movement

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::read_price_movement() {
  this->price_movement = this->quoter.read_price_movement(this->symbol);
}

#endif

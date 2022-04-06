#ifndef ALPACA__TAO_BOT_set_price_movements
#define ALPACA__TAO_BOT_set_price_movements

#include "hedge_symbol.cpp"       // hedge_symbol
#include "is_hedging.cpp"         // is_hedging
#include "set_price_movement.cpp" // set_price_movement
#include "tao_bot.h"              // Alpaca::TaoBot

void Alpaca::TaoBot::set_price_movements() {
  set_price_movement(this->symbol, this->quotes);

  if (is_hedging()) {
    set_price_movement(hedge_symbol(), this->hedge_quotes);
  }
}

#endif

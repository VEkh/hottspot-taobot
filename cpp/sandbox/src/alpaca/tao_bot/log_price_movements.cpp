#ifndef ALPACA__TAO_BOT_log_price_movements
#define ALPACA__TAO_BOT_log_price_movements

#include "hedge_symbol.cpp"       // hedge_symbol
#include "is_hedging.cpp"         // is_hedging
#include "log_price_movement.cpp" // log_price_movement
#include "tao_bot.h"              // Alpaca::TaoBot

void Alpaca::TaoBot::log_price_movements() {
  log_price_movement(this->symbol);

  if (is_hedging()) {
    log_price_movement(hedge_symbol());
  }
}

#endif

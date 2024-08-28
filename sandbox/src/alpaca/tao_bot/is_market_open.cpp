#ifndef ALPACA__TAO_BOT_is_market_open
#define ALPACA__TAO_BOT_is_market_open

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::is_market_open() {
  return this->market_availability.is_market_open(this->current_epoch);
}

#endif

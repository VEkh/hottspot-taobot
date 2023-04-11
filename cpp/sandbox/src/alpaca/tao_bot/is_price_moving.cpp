#ifndef ALPACA__TAO_BOT_is_price_moving
#define ALPACA__TAO_BOT_is_price_moving

#include "tao_bot.h" // Alpaca::TaoBot, quote_t

bool Alpaca::TaoBot::is_price_moving() {
  if (this->quotes.size() < 2) {
    return false;
  }

  return this->quotes.front().price != this->quotes.at(1).price;
}

#endif

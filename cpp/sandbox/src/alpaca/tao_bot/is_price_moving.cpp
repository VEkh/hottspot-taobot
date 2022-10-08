#ifndef ALPACA__TAO_BOT_is_price_moving
#define ALPACA__TAO_BOT_is_price_moving

#include "tao_bot.h" // Alpaca::TaoBot, quote_t

bool Alpaca::TaoBot::is_price_moving() {
  return this->quotes.back().price !=
         this->quotes.at(this->quotes.size() - 2).price;
}

#endif

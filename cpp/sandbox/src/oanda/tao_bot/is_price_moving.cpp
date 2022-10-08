#ifndef OANDA__TAO_BOT_is_price_moving
#define OANDA__TAO_BOT_is_price_moving

#include "tao_bot.h" // Oanda::TaoBot, quote_t

bool Oanda::TaoBot::is_price_moving() {
  return this->quotes.back().price !=
         this->quotes.at(this->quotes.size() - 2).price;
}

#endif

#ifndef ALPACA__TAO_BOT_current_mid
#define ALPACA__TAO_BOT_current_mid

#include "tao_bot.h" // Alpaca::TaoBot, quote_t

double Alpaca::TaoBot::current_mid() {
  if (this->quotes.empty()) {
    return quote_t().mid();
  }

  return this->quotes.front().mid();
}

#endif

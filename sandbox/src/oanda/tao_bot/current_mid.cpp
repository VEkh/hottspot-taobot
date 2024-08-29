#ifndef OANDA__TAO_BOT_current_mid
#define OANDA__TAO_BOT_current_mid

#include "tao_bot.h" // Oanda::TaoBot, quote_t

double Oanda::TaoBot::current_mid() {
  if (!this->current_quote.ask) {
    return quote_t().mid();
  }

  return this->current_quote.mid();
}

#endif

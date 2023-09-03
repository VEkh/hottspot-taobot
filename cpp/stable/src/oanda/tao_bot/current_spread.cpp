#ifndef OANDA__TAO_BOT_current_spread
#define OANDA__TAO_BOT_current_spread

#include "tao_bot.h" // Oanda::TaoBot, quote_t

double Oanda::TaoBot::current_spread() {
  const quote_t current_quote = this->quotes.back();
  return current_quote.ask - current_quote.bid;
}

#endif

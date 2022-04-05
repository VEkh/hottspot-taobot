#ifndef ALPACA__TAO_BOT_fetch_quotes
#define ALPACA__TAO_BOT_fetch_quotes

#include "fetch_quote.cpp"  // fetch_quote
#include "hedge_symbol.cpp" // hedge_symbol
#include "is_hedging.cpp"   // is_hedging
#include "tao_bot.h"        // Alpaca::TaoBot, quote_t
#include <string>           // std::string

void Alpaca::TaoBot::fetch_quotes() {
  const quote_t current_quote = fetch_quote(this->symbol);
  this->quotes.push_back(current_quote);

  if (is_hedging()) {
    const quote_t current_hedge_quote = fetch_quote(hedge_symbol());
    this->hedge_quotes.push_back(current_hedge_quote);
  }
}

#endif

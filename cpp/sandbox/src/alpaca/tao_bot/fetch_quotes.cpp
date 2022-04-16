#ifndef ALPACA__TAO_BOT_fetch_quotes
#define ALPACA__TAO_BOT_fetch_quotes

#include "fetch_quote.cpp"  // fetch_quote
#include "hedge_symbol.cpp" // hedge_symbol
#include "is_hedging.cpp"   // is_hedging
#include "tao_bot.h"        // Alpaca::TaoBot, quote_t
#include "write_quotes.cpp" // write_quotes
#include <string>           // std::string

void Alpaca::TaoBot::fetch_quotes() {
  const quote_t current_quote = fetch_quote(this->symbol);

  this->quotes.push_back(current_quote);
  write_quotes(this->quotes, this->symbol);

  if (is_hedging()) {
    const std::string hedge_symbol_ = hedge_symbol();
    const quote_t current_hedge_quote = fetch_quote(hedge_symbol_);

    this->hedge_quotes.push_back(current_hedge_quote);
    write_quotes(this->hedge_quotes, hedge_symbol_);
  }
}

#endif

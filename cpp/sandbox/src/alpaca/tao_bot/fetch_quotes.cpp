#ifndef ALPACA__TAO_BOT_fetch_quotes
#define ALPACA__TAO_BOT_fetch_quotes

#include "get_quote.cpp"    // get_quote
#include "hedge_symbol.cpp" // hedge_symbol
#include "tao_bot.h"        // Alpaca::TaoBot, quote_t
#include "write_quotes.cpp" // write_quotes
#include <string>           // std::string

void Alpaca::TaoBot::fetch_quotes() {
  const quote_t current_quote = get_quote(this->symbol);

  this->quotes[this->symbol].push_back(current_quote);
  write_quotes(this->symbol);

  const std::string hedge_symbol_ = hedge_symbol();
  const quote_t current_hedge_quote = get_quote(hedge_symbol_);

  this->quotes[hedge_symbol_].push_back(current_hedge_quote);
  write_quotes(hedge_symbol_);
}

#endif

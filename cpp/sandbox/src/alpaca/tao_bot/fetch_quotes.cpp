#ifndef ALPACA__TAO_BOT_fetch_quotes
#define ALPACA__TAO_BOT_fetch_quotes

#include "get_quote.cpp"    // get_quote
#include "tao_bot.h"        // Alpaca::TaoBot, quote_t
#include "write_quotes.cpp" // write_quotes
#include <string>           // std::string

void Alpaca::TaoBot::fetch_quotes() {
  const quote_t current_quote = get_quote(this->symbol);

  this->quotes[this->symbol].push_back(current_quote);
  write_quotes(this->symbol);
}

#endif

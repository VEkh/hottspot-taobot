#ifndef ALPACA__TAO_BOT_fetch_and_persist_quote
#define ALPACA__TAO_BOT_fetch_and_persist_quote

#include "get_quote.cpp"    // get_quote
#include "tao_bot.h"        // Alpaca::TaoBot, quote_t
#include "write_quotes.cpp" // write_quotes
#include <string>           // std::string

void Alpaca::TaoBot::fetch_and_persist_quote() {
  const quote_t current_quote = get_quote(this->symbol);

  this->quotes[this->symbol].push_back(current_quote);
  write_quotes();
}

#endif

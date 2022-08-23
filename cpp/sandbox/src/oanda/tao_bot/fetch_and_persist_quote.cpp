#ifndef OANDA__TAO_BOT_fetch_and_persist_quote
#define OANDA__TAO_BOT_fetch_and_persist_quote

#include "fetch_quote.cpp"  // fetch_quote
#include "tao_bot.h"        // Oanda::TaoBot, quote_t
#include "write_quotes.cpp" // write_quotes
#include <string>           // std::string

void Oanda::TaoBot::fetch_and_persist_quote() {
  fetch_quote();
  write_quotes();
}

#endif

#ifndef ETRADE__TAO_BOT_fetch_quote
#define ETRADE__TAO_BOT_fetch_quote

/*
 * ETrade::TaoBot
 * quote_t
 */
#include "tao_bot.h"

#include <string> // std::string

void ETrade::TaoBot::fetch_quote() {
  std::string quote_string = this->etrade_client.fetch_quote(this->symbol);
  quote_t current_quote = this->etrade_client.parse_quote(quote_string);

  this->quotes.push_back(current_quote);
}

#endif

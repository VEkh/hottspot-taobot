#ifndef ALPACA__TAO_BOT_fetch_quote
#define ALPACA__TAO_BOT_fetch_quote

#include "tao_bot.h" // Alpaca::TaoBot, quote_t
#include <string>    // std::string

void Alpaca::TaoBot::fetch_quote() {
  const std::string quote_string = this->api_client.fetch_quote(this->symbol);
  const quote_t current_quote = this->api_client.parse_quote(quote_string);

  this->quotes.push_back(current_quote);
}

#endif

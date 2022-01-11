#ifndef OANDA__TAO_BOT_fetch_quote
#define OANDA__TAO_BOT_fetch_quote

#include "tao_bot.h" // Oanda::TaoBot, quote_t
#include <string>    // std::string

void Oanda::TaoBot::fetch_quote() {
  const std::string quote_string = this->api_client.fetch_quote(this->symbol);
  const quote_t current_quote = this->api_client.parse_quote(quote_string);

  this->quotes.push_back(current_quote);
}

#endif

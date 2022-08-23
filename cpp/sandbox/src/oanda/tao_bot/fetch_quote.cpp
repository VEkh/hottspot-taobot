#ifndef OANDA__TAO_BOT_fetch_quote
#define OANDA__TAO_BOT_fetch_quote

#include "deps.cpp"          // json, nlohmann
#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Oanda::TaoBot, quote_t
#include <string>            // std::string

void Oanda::TaoBot::fetch_quote() {
  try {
    const std::string quote_string = this->api_client.fetch_quote(this->symbol);
    quote_t parsed_quote = this->api_client.parse_quote(quote_string);
    parsed_quote.symbol = this->symbol;

    this->quotes.push_back(parsed_quote);
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string("OANDA__TAO_BOT_fetch_quote error when parsing"));

    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote();
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(
        std::string("OANDA__TAO_BOT_fetch_quote error when reading the quote"));

    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote();
  }
}

#endif

#ifndef ALPACA__TAO_BOT_fetch_quote
#define ALPACA__TAO_BOT_fetch_quote

#include "deps.cpp"  // nlohmann
#include "tao_bot.h" // Alpaca::TaoBot, quote_t
#include <string>    // std::string

void Alpaca::TaoBot::fetch_quote() {
  try {
    const std::string quote_string = this->api_client.fetch_quote(this->symbol);
    const quote_t current_quote = this->api_client.parse_quote(quote_string);

    this->quotes.push_back(current_quote);
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string("ALPACA__TAO_BOT_fetch_quote error when parsing"));

    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote();
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(std::string(
        "ALPACA__TAO_BOT_fetch_quote error when reading the quote"));

    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote();
  }
}

#endif

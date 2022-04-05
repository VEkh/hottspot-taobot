#ifndef ALPACA__TAO_BOT_fetch_quote
#define ALPACA__TAO_BOT_fetch_quote

#include "deps.cpp"  // nlohmann
#include "tao_bot.h" // Alpaca::TaoBot, quote_t
#include <string>    // std::string

Alpaca::TaoBot::quote_t Alpaca::TaoBot::fetch_quote(const std::string symbol_) {
  try {
    const std::string quote_string = this->api_client.fetch_quote(symbol_);
    quote_t parsed_quote = this->api_client.parse_quote(quote_string);
    parsed_quote.symbol = symbol_.c_str();

    return parsed_quote;
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string("ALPACA__TAO_BOT_fetch_quote error when parsing"));

    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol_);
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(std::string(
        "ALPACA__TAO_BOT_fetch_quote error when reading the quote"));

    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol_);
  }
}

#endif

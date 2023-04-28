#ifndef OANDA__QUOTE_fetch_quote
#define OANDA__QUOTE_fetch_quote

#include "deps.cpp"          // nlohmann
#include "lib/formatted.cpp" // Formatted
#include "quote.h"           // Oanda::Quote, quote_t
#include <string>            // std::string

Oanda::Quote::quote_t Oanda::Quote::fetch_quote(const std::string symbol) {
  try {
    const std::string quote_string = this->api_client.fetch_quote(symbol);
    quote_t parsed_quote = this->api_client.parse_quote(quote_string);
    parsed_quote.symbol = symbol;

    return parsed_quote;
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string("[OANDA__QUOTE_fetch_quote]: Error when parsing"));

    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol);
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(std::string(
        "[OANDA__QUOTE_fetch_quote]: Error when reading the quote"));

    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol);
  }
}

#endif

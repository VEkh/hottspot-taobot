#ifndef OANDA__QUOTE_get_quote
#define OANDA__QUOTE_get_quote

#include "deps.cpp"          // json, nlohmann
#include "fetch_quote.cpp"   // fetch_quote
#include "lib/formatted.cpp" // Formatted
#include "quote.h"           // Oanda::Quote, quote_t
#include <iostream>          // std::cout, std::endl
#include <string>            // std::string

Oanda::Quote::quote_t Oanda::Quote::get_quote(const std::string symbol) {
  try {
    return fetch_quote(symbol);
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        "[OANDA__QUOTE_get_quote]: nlohmann::detail::parse_error "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol);
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(
        "[OANDA__QUOTE_get_quote]: nlohmann::detail::type_error "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol);
  }
}

#endif

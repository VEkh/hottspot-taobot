#ifndef ALPACA__QUOTE_get_quote
#define ALPACA__QUOTE_get_quote

#include "deps.cpp"               // json, nlohmann
#include "fetch_quote.cpp"        // fetch_quote
#include "get_streamed_quote.cpp" // get_streamed_quote
#include "lib/formatted.cpp"      // Formatted
#include "quote.h"                // Alpaca::Quote, quote_t
#include <iostream>               // std::cout, std::endl
#include <string>                 // std::string

Alpaca::Quote::quote_t Alpaca::Quote::get_quote(const std::string symbol) {
  try {
    return get_streamed_quote(symbol);
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__QUOTE_get_quote]: nlohmann::detail::parse_error "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol);
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__QUOTE_get_quote]: nlohmann::detail::type_error "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol);
  } catch (std::domain_error &e) {
    std::string error_message =
        Formatted::error_message("[ALPACA__QUOTE_get_quote]: std::domain_error "
                                 "when streaming: ");
    std::cout << error_message << e.what() << fmt.reset << std::endl;

    return fetch_quote(symbol);
  } catch (std::invalid_argument &) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__QUOTE_get_quote]: std::invalid_argument "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote(symbol);
  }
}

#endif

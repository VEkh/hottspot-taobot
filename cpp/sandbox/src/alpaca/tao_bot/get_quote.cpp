#ifndef ALPACA__TAO_BOT_get_quote
#define ALPACA__TAO_BOT_get_quote

#include "deps.cpp"                // json, nlohmann
#include "fetch_quote.cpp"         // fetch_quote
#include "lib/formatted.cpp"       // Formatted
#include "read_streamed_quote.cpp" // read_streamed_quote
#include "tao_bot.h"               // Alpaca::TaoBot, quote_t
#include <iostream>                // std::cout, std::endl
#include <string>                  // std::string

Alpaca::TaoBot::quote_t Alpaca::TaoBot::get_quote() {
  try {
    return read_streamed_quote();
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_quote]: nlohmann::detail::parse_error "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote();
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_quote]: nlohmann::detail::type_error "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote();
  } catch (std::domain_error &e) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_quote]: std::domain_error "
        "when streaming: ");
    std::cout << error_message << e.what() << fmt.reset << std::endl;

    return fetch_quote();
  } catch (std::invalid_argument &) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_quote]: std::invalid_argument "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    return fetch_quote();
  }
}

#endif

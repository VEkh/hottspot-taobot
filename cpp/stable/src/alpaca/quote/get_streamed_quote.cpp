#ifndef ALPACA__QUOTE_get_streamed_quote
#define ALPACA__QUOTE_get_streamed_quote

#include "lib/formatted.cpp" // Formatted
#include "quote.h"           // Alpaca::Quote, quote_t
#include <stdexcept>         // std::domain_error
#include <string>            // std::string
#include <time.h>            // time

Alpaca::Quote::quote_t
Alpaca::Quote::get_streamed_quote(const std::string symbol) {
  const quote_t quote = this->db_streamed_quote.get({.symbol = symbol});

  const double now = time(nullptr);

  if (!quote.ask || !quote.bid) {
    const std::string error_message = Formatted::error_message(
        symbol + " streamed quote doesn't exist. Falling back to fetch.");

    throw std::domain_error(error_message);
  }

  if ((now - quote.timestamp) > 10) {
    const std::string error_message = Formatted::error_message(
        symbol + " quote stale. Falling back to fetch.");

    throw std::domain_error(error_message);
  }

  return quote;
}

#endif

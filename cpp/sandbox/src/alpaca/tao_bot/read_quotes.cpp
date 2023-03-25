#ifndef ALPACA__TAO_BOT_read_quotes
#define ALPACA__TAO_BOT_read_quotes

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Alpaca::TaoBot, quote_t
#include <stdexcept>         // std::runtime_error
#include <vector>            // std::vector

void Alpaca::TaoBot::read_quotes() {
  const std::vector<quote_t> quotes_ = this->quoter.db_quote.get_last({
      .debug = false,
      .limit = 2,
      .symbol = this->symbol,
  });

  if (quotes_.empty()) {
    const std::string error_message = Formatted::error_message(
        "No available quotes for " + this->symbol + " in the database.");
    throw std::runtime_error(error_message);
  }

  this->quotes = quotes_;
}

#endif

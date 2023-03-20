#ifndef ALPACA__TAO_BOT_read_quotes
#define ALPACA__TAO_BOT_read_quotes

#include "tao_bot.h" // Alpaca::TaoBot, quote_t
#include <vector>    // std::vector

void Alpaca::TaoBot::read_quotes() {
  const std::vector<quote_t> quotes_ = this->quoter.db_quote.get_last({
      .debug = false,
      .limit = 2,
      .symbol = this->symbol,
  });

  if (quotes_.empty()) {
    return read_quotes();
  }

  this->quotes = quotes_;
}

#endif

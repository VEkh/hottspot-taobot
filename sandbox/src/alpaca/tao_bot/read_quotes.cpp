#ifndef ALPACA__TAO_BOT_read_quotes
#define ALPACA__TAO_BOT_read_quotes

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Alpaca::TaoBot, quote_t
#include <list>              // std::list

void Alpaca::TaoBot::read_quotes() {
  const std::list<quote_t> quotes_ = this->quoter.db_quote.get_last({
      .debug = this->api_client.config.debug_sql,
      .limit = 2,
      .limit_offset = 0,
      .symbol = this->symbol,
      .timestamp_upper_bound = this->current_epoch,
  });

  if (quotes_.empty()) {
    const std::string error_message = Formatted::error_message(
        "No available quotes for " + this->symbol + " in the database.");

    printf("%s\n", error_message.c_str());

    return read_quotes();
  }

  this->quotes = quotes_;
}

#endif

#ifndef OANDA__TAO_BOT_read_quotes
#define OANDA__TAO_BOT_read_quotes

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Oanda::TaoBot, quote_t
#include <vector>            // std::vector

void Oanda::TaoBot::read_quotes() {
  const std::vector<quote_t> quotes_ = this->db_quote.get_last({
      .limit = 2,
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

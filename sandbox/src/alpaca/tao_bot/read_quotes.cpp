#ifndef ALPACA__TAO_BOT_read_quotes
#define ALPACA__TAO_BOT_read_quotes

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Alpaca::TaoBot, quote_t
#include <list>              // std::list

#include "advance_current_epoch.cpp" // advance_current_epoch

void Alpaca::TaoBot::read_quotes() {
  if (this->backtest.is_active &&
      this->quoter.db_quote.cache.is_expired(this->current_epoch)) {
    this->quoter.db_quote.get_last({
        .debug = this->api_client.config.debug_sql,
        .end_at = this->market_close_epoch,
        .start_at = this->current_epoch,
        .symbol = this->symbol,
        .write_cache = true,
    });
  }

  if (!this->quotes.empty()) {
    this->previous_quote = this->quotes.back();
  }

  const std::list<quote_t> quotes_ = this->quoter.db_quote.get_last({
      .debug = this->api_client.config.debug_sql,
      .end_at = this->current_epoch,
      .limit = 1,
      .limit_offset = 0,
      .read_cache = this->backtest.is_active,
      .sort_direction = "desc",
      .symbol = this->symbol,
  });

  if (quotes_.empty()) {
    const std::string error_message = Formatted::error_message(
        "No available quotes for " + this->symbol + " in the database.");

    printf("%s\n", error_message.c_str());

    if (this->backtest.is_active) {
      advance_current_epoch();
    }

    return read_quotes();
  }

  this->current_quote = quotes_.front();
  this->quotes = quotes_;
}

#endif

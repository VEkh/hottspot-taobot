#ifndef ALPACA__TAO_BOT_read_quotes
#define ALPACA__TAO_BOT_read_quotes

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Alpaca::TaoBot, quote_t
#include <list>              // std::list
#include <string>            // std::string

void Alpaca::TaoBot::read_quotes() {
  // TODO: Delete
  // if (this->backtest.is_active &&
  //     this->quoter.db_quote.cache.is_expired(this->current_epoch)) {
  //   this->quoter.db_quote.get_last({
  //       .debug = this->api_client.config.debug_sql,
  //       .end_at = this->market_close_epoch,
  //       .sort_direction = "asc",
  //       .start_at = this->current_epoch,
  //       .symbol = this->symbol,
  //       .write_cache = true,
  //   });
  // }

  double end_at = this->current_epoch;
  double start_at = 0;
  int limit = 1;
  std::string sort_direction = "desc";

  if (this->backtest.is_active) {
    end_at = this->market_close_epoch;
    limit = 0;
    sort_direction = "asc";
    start_at = this->current_epoch;
  }

  const std::list<quote_t> quotes_ = this->quoter.db_quote.get_last({
      .debug = this->api_client.config.debug_sql,
      .end_at = end_at,
      .limit = limit,
      .sort_direction = sort_direction,
      .start_at = start_at,
      .symbol = this->symbol,
  });

  if (quotes_.empty()) {
    const std::string error_message = Formatted::error_message(
        "No available quotes for " + this->symbol + " in the database.");

    printf("%s @ %f\n", error_message.c_str(), this->current_epoch);

    return read_quotes();
  }

  this->quotes = quotes_;
}

#endif

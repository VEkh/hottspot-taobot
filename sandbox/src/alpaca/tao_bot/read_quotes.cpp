#ifndef ALPACA__TAO_BOT_read_quotes
#define ALPACA__TAO_BOT_read_quotes

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, quote_t
#include <list>               // std::list
#include <string>             // std::string

void Alpaca::TaoBot::read_quotes() {
  double end_at = this->current_epoch;
  double start_at = 0;
  int limit = 1;
  std::string sort_direction = "desc";

  if (this->backtest.is_active) {
    end_at = this->market_close_epoch;
    start_at = this->current_epoch;
    limit = 0;
    sort_direction = "asc";
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
    std::cout << fmt.bold << fmt.red;
    printf("No available quotes for %s in the database @ %s\n",
           this->symbol.c_str(),
           ::utils::time_::date_string(this->current_epoch, "%F %R CT",
                                       "America/Chicago")
               .c_str());

    std::cout << fmt.yellow;
    printf("⌛ Advancing epoch...\n");
    std::cout << fmt.reset << std::endl;

    if (this->backtest.is_active) {
      advance_current_epoch(this->current_epoch + 1);
    } else {
      advance_current_epoch();
    }

    return this->market_availability.is_end_of_trading_period(
               this->current_epoch)
               ? void()
               : read_quotes();
  }

  this->quotes = quotes_;
}

#endif

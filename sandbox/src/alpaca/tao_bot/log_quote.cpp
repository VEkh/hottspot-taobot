#ifndef ALPACA__TAO_BOT_log_quote
#define ALPACA__TAO_BOT_log_quote

/*
 * Alpaca::TaoBot
 * fmt
 * quote_t
 */
#include "tao_bot.h"

#include "current_mid.cpp"          // current_mid
#include "day_range_percentile.cpp" // day_range_percentile
#include "lib/formatted.cpp"        // Formatted
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf

void Alpaca::TaoBot::log_quote() {
  Formatted::Stream log_color = fmt.yellow;

  if (!this->previous_quote.ask) {
    return;
  }

  if (this->current_quote.mid() > this->previous_quote.mid()) {
    log_color = fmt.green;
  } else if (this->current_quote.mid() < this->previous_quote.mid()) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Quote\n", this->current_quote.symbol.c_str());
  std::cout << fmt.no_underline;

  const double day_range = this->day_candle.range();
  const double price_action = 100.0 * day_range / this->day_candle.open;

  printf("Current: %'.2f • High: %'.2f • Low: %'.2f • Δ %'.2f (%.2f%% of Open) "
         "• p%'.2f%%\n",
         this->current_quote.price, this->day_candle.high, this->day_candle.low,
         day_range, price_action, day_range_percentile(current_mid()));
  std::cout << fmt.reset << std::endl;
}

#endif

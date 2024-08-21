#ifndef ALPACA__TAO_BOT_log_quote
#define ALPACA__TAO_BOT_log_quote

#include "current_mid.cpp"          // current_mid
#include "day_range_percentile.cpp" // day_range_percentile
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/time.cpp"       // ::utils::time_
#include "tao_bot.h"                // Alpaca::TaoBot, fmt
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

  printf("Current: %'.2f (p%'.2f%%) • High: %'.2f @ %s • Low: %'.2f @ %s\n",
         this->current_quote.price, day_range_percentile(current_mid()),
         this->day_candle.high,
         ::utils::time_::date_string(this->day_candle.high_at, "%R CT",
                                     "America/Chicago")
             .c_str(),
         this->day_candle.low,
         ::utils::time_::date_string(this->day_candle.low_at, "%R CT",
                                     "America/Chicago")
             .c_str());

  std::cout << fmt.reset << std::endl;
}

#endif

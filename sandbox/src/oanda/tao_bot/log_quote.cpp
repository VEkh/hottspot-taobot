#ifndef OANDA__TAO_BOT_log_quote
#define OANDA__TAO_BOT_log_quote

#include "current_mid.cpp"          // current_mid
#include "day_range_percentile.cpp" // day_range_percentile
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/time.cpp"       // ::utils::time_
#include "tao_bot.h"                // Oanda::TaoBot, fmt
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf

void Oanda::TaoBot::log_quote() {
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
  printf("%s Quote", this->current_quote.symbol.c_str());
  std::cout << fmt.no_underline << std::endl;

  printf("Current: %'.5f (p%'.2f%%) • Spread: %'.5f", this->current_quote.mid(),
         day_range_percentile(this->day_candle, current_mid()),
         this->current_quote.spread());
  std::cout << std::endl;

  printf("High: %'.5f @ %s • Low: %'.5f @ %s • Δ: %'.5f\n",
         this->day_candle.high,
         ::utils::time_::date_string(this->day_candle.high_at, "%m/%d %R %Z",
                                     "America/Chicago")
             .c_str(),
         this->day_candle.low,
         ::utils::time_::date_string(this->day_candle.low_at, "%m/%d %R %Z",
                                     "America/Chicago")
             .c_str(),
         this->day_candle.range());

  std::cout << fmt.reset << std::endl;
}

#endif

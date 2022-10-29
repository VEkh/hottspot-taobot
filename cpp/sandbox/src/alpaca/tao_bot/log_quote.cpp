#ifndef ALPACA__TAO_BOT_log_quote
#define ALPACA__TAO_BOT_log_quote

/*
 * Alpaca::TaoBot
 * fmt
 * quote_t
 */
#include "tao_bot.h"

#include "get_quote_price_range.cpp" // get_quote_price_range
#include "lib/formatted.cpp"         // Formatted
#include "lib/utils/float.cpp"       // utils::float_
#include <iostream>                  // std::cout, std::endl
#include <stdio.h>                   // printf

void Alpaca::TaoBot::log_quote() {
  Formatted::Stream log_color = fmt.yellow;

  const int ticks = this->quotes.size();

  if (!ticks) {
    return;
  }

  const std::pair<double, double> quote_range = get_quote_price_range();

  const quote_t *previous_quote =
      ticks > 1 ? &(this->quotes.at(ticks - 2)) : nullptr;

  const quote_t current_quote = this->quotes.back();

  if (previous_quote) {
    if (current_quote.price > previous_quote->price) {
      log_color = fmt.green;
    } else if (current_quote.price < previous_quote->price) {
      log_color = fmt.red;
    }
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Quote (%i Min Range)\n", current_quote.symbol.c_str(),
         this->CONSOLIDATION_TIME_SECONDS / 60);
  std::cout << fmt.no_underline;

  printf("Current: %'.2f", ::utils::float_::to_currency(current_quote.price));
  std::cout << fmt.yellow << " • ";

  std::cout << fmt.green;
  printf("High: %'.2f", ::utils::float_::to_currency(quote_range.first));
  std::cout << fmt.yellow << " • ";

  std::cout << fmt.red;
  printf("Low: %'.2f\n", ::utils::float_::to_currency(quote_range.second));

  std::cout << fmt.reset << std::endl;
}

#endif

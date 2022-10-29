#ifndef OANDA__TAO_BOT_log_quote
#define OANDA__TAO_BOT_log_quote

/*
 * Oanda::TaoBot
 * fmt
 * quote_t
 */
#include "tao_bot.h"

#include "get_quote_price_range.cpp" // get_quote_price_range
#include "lib/formatted.cpp"         // Formatted
#include "lib/utils/integer.cpp"     // utils::integer_
#include <iostream>                  // std::cout, std::endl
#include <stdio.h>                   // printf

void Oanda::TaoBot::log_quote() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = this->quotes.size();

  if (!ticks) {
    return;
  }

  const quote_t *previous_quote =
      ticks > 1 ? &(this->quotes.at(ticks - 2)) : nullptr;
  const quote_t current_quote = this->quotes.back();
  const quote_t first_quote = this->quotes.front();
  const std::pair<double, double> quote_range = get_quote_price_range();

  if (previous_quote) {
    if (current_quote.price > previous_quote->price) {
      log_color = fmt.green;
    } else if (current_quote.price < previous_quote->price) {
      log_color = fmt.red;
    }
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Quote (%i Min Range)\n", this->symbol,
         this->CONSOLIDATION_TIME_SECONDS / 60);
  std::cout << fmt.no_underline;

  printf("Bid: %'.5f • Mid: %'.5f • Ask: %'.5f • Spread: %'.5f\n",
         current_quote.bid, current_quote.price, current_quote.ask,
         current_quote.ask - current_quote.bid);

  std::cout << fmt.green;
  printf("High: %'.5f", ::utils::float_::to_currency(quote_range.first));
  std::cout << fmt.yellow << " • ";

  std::cout << fmt.red;
  printf("Low: %'.5f\n", ::utils::float_::to_currency(quote_range.second));

  std::cout << fmt.reset << std::endl;
}

#endif

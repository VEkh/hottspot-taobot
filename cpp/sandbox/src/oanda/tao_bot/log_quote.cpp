#ifndef OANDA__TAO_BOT_log_quote
#define OANDA__TAO_BOT_log_quote

/*
 * Oanda::TaoBot
 * fmt
 * quote_t
 */
#include "tao_bot.h"

#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/integer.cpp" // utils::integer_
#include <iomanip>               // std::setprecision
#include <iostream>              // std::cout, std::endl, std::fixed
#include <stdio.h>               // printf

void Oanda::TaoBot::log_quote() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = this->quotes.size();

  if (!ticks) {
    return;
  }

  const quote_t *previous_quote = ticks > 1 ? &(quotes.at(ticks - 2)) : nullptr;
  const quote_t current_quote = quotes.back();
  const quote_t first_quote = quotes.front();

  if (previous_quote) {
    if (current_quote.price > previous_quote->price) {
      log_color = fmt.green;
    } else if (current_quote.price < previous_quote->price) {
      log_color = fmt.red;
    }
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Quote\n", this->symbol);

  std::cout << fmt.reset << fmt.bold << log_color;
  printf("Bid: %'.5f • Mid: %'.5f • Ask: %'.5f • Spread: %'.5f\n",
         current_quote.bid, current_quote.price, current_quote.ask,
         current_quote.ask - current_quote.bid);

  std::cout << fmt.reset << std::endl;
}

#endif

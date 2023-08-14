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
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

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

  if (previous_quote) {
    if (current_quote.price > previous_quote->price) {
      log_color = fmt.green;
    } else if (current_quote.price < previous_quote->price) {
      log_color = fmt.red;
    }
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Quote\n", this->symbol.c_str());
  std::cout << fmt.no_underline;

  printf("Bid: %'.5f • Mid: %'.5f • Ask: %'.5f • Spread: %'.5f\n",
         current_quote.bid, current_quote.price, current_quote.ask,
         current_quote.ask - current_quote.bid);

  std::cout << fmt.reset << std::endl;
}

#endif

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
  const int runtime = current_quote.timestamp - first_quote.timestamp;

  if (previous_quote) {
    if (current_quote.price > previous_quote->price) {
      log_color = fmt.green;
    } else if (current_quote.price < previous_quote->price) {
      log_color = fmt.red;
    }
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Quote @ %s\n", this->symbol,
         ::utils::integer_::seconds_to_clock(runtime).c_str());

  std::cout << fmt.reset << fmt.bold << log_color;
  printf("Current: %'.5f\n", current_quote.price);

  std::cout << fmt.reset << std::endl;
}

#endif
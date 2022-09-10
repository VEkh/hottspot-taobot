#ifndef ALPACA__TAO_BOT_fetch_and_persist_quote
#define ALPACA__TAO_BOT_fetch_and_persist_quote

#include "current_price.cpp" // current_price
#include "get_quote.cpp"     // get_quote
#include "tao_bot.h"         // Alpaca::TaoBot, fmt, quote_t
#include "write_quotes.cpp"  // write_quotes
#include <iostream>          // std::cout, std::endl
#include <math.h>            // abs

void Alpaca::TaoBot::fetch_and_persist_quote() {
  const quote_t new_quote = get_quote();

  const double current_price_ = current_price();
  const double delta_ratio =
      (new_quote.price - current_price_) / current_price_;

  if (abs(delta_ratio) >= 0.1) {
    std::cout << fmt.bold << fmt.yellow;
    puts("🧐 STRANGE PRICE MOVEMENT");
    printf("Last Quote: %.2f • New Quote: %.2f\n", current_price_,
           new_quote.price);
    std::cout << fmt.reset << std::endl;

    return fetch_and_persist_quote();
  }

  this->quotes.push_back(new_quote);
  write_quotes();
}

#endif

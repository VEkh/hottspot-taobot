#ifndef ALPACA__QUOTE_fetch_and_persist_quote
#define ALPACA__QUOTE_fetch_and_persist_quote

#include "get_quote.cpp" // get_quote
#include "quote.h"       // Alpaca::Quote, fmt, quote_t
#include <iostream>      // std::cout, std::endl
#include <math.h>        // abs
#include <string>        // std::string

void Alpaca::Quote::fetch_and_persist_quote(
    const std::string symbol, const bool skip_anomaly_check = false) {
  const quote_t new_quote = get_quote(symbol);

  const double current_price_ = this->current_quote.price;

  const double delta_ratio =
      (new_quote.price - current_price_) / current_price_;

  if (!skip_anomaly_check && abs(delta_ratio) >= 0.01) {
    std::cout << fmt.bold << fmt.yellow;
    puts("🧐 STRANGE PRICE MOVEMENT");
    printf("Last Quote: %.2f • New Quote: %.2f\n", current_price_,
           new_quote.price);
    std::cout << fmt.reset << std::endl;

    return fetch_and_persist_quote(symbol);
  }

  db_quote.upsert(new_quote);

  this->previous_quote = !current_price_ ? new_quote : this->current_quote;
  this->current_quote = new_quote;
}

#endif

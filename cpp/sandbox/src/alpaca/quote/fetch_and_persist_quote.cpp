#ifndef ALPACA__QUOTE_fetch_and_persist_quote
#define ALPACA__QUOTE_fetch_and_persist_quote

#include "current_price.cpp"    // current_price
#include "get_quote.cpp"        // get_quote
#include "quote.h"              // Alpaca::Quote, fmt, quote_t
#include "write_collection.cpp" // write_collection
#include <iostream>             // std::cout, std::endl
#include <math.h>               // abs
#include <string>               // std::string

void Alpaca::Quote::fetch_and_persist_quote(
    const std::string symbol, const bool skip_anomaly_check = false) {
  const quote_t new_quote = get_quote(symbol);

  const double current_price_ =
      this->quotes[symbol].size() ? current_price(symbol) : new_quote.price;

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

  this->quotes[symbol].push_back(new_quote);

  if (this->quotes[symbol].size() > this->QUOTES_MAX_SIZE) {
    const int offset = this->quotes[symbol].size() - this->QUOTES_MAX_SIZE;
    const std::vector<quote_t> limited_quotes(
        this->quotes[symbol].begin() + offset, this->quotes[symbol].end());

    this->quotes[symbol] = limited_quotes;
  }

  write_collection(symbol);
}

#endif

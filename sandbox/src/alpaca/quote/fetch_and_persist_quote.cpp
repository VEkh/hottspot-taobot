#ifndef ALPACA__QUOTE_fetch_and_persist_quote
#define ALPACA__QUOTE_fetch_and_persist_quote

#include "get_quote.cpp" // get_quote
#include "quote.h"       // Alpaca::Quote, fmt, quote_t
#include <iostream>      // std::cout, std::endl
#include <math.h>        // abs
#include <string>        // std::string
#include <unistd.h>      // usleep

void Alpaca::Quote::fetch_and_persist_quote(
    const std::string symbol, const bool skip_anomaly_check = false) {
  const quote_t new_quote = get_quote(symbol);

  const double current_mid_ = this->current_quotes[symbol].mid();

  const double delta_ratio = (new_quote.mid() - current_mid_) / current_mid_;

  if (!skip_anomaly_check && abs(delta_ratio) >= 0.01) {
    std::cout << fmt.bold << fmt.yellow;
    puts("🧐 STRANGE PRICE MOVEMENT");
    printf("Last Quote: %.2f • New Quote: %.2f\n", current_mid_,
           new_quote.mid());
    std::cout << fmt.reset << std::endl;

    usleep(5e5);

    return fetch_and_persist_quote(symbol);
  }

  this->db_quote.upsert(new_quote);

  this->previous_quotes[symbol] =
      !current_mid_ ? new_quote : this->current_quotes[symbol];
  this->current_quotes[symbol] = new_quote;
}

#endif

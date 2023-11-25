#ifndef ALPACA__QUOTE_watch
#define ALPACA__QUOTE_watch

#include "alpaca/utils.cpp"            // Alpaca::Utils
#include "fetch_and_persist_quote.cpp" // fetch_and_persist_quote
#include "quote.h"                     // Alpaca::Quote
#include <iostream>                    // std::cout, std::endl, std::flush
#include <list>                        // std::list
#include <stdio.h>                     // printf, puts
#include <string>                      // std::string
#include <unistd.h>                    // usleep

void Alpaca::Quote::watch(const std::list<std::string> &symbols) {
  bool is_market_open = Alpaca::Utils::is_market_open(time(nullptr), -30 * 60);

  if (is_market_open) {
    for (const std::string symbol : symbols) {
      fetch_and_persist_quote(symbol, true);
    }
  }

  while (is_market_open) {
    for (const std::string symbol : symbols) {
      std::cout << fmt.bold << fmt.cyan << fmt.underline;
      puts(symbol.c_str());
      std::cout << fmt.reset;

      fetch_and_persist_quote(symbol);

      const quote_t current_quote = this->current_quotes[symbol];

      this->db_quote.upsert_avg_one_sec_variance({
          .id = current_quote.id,
          .symbol = symbol,
          .debug = true,
      });
    }

    std::cout << std::flush;
    usleep(5e5);

    is_market_open = Alpaca::Utils::is_market_open(time(nullptr), -30 * 60);
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("😴 Market is closed\n");
  std::cout << fmt.reset;
}

#endif

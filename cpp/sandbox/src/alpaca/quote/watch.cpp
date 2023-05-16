#ifndef ALPACA__QUOTE_watch
#define ALPACA__QUOTE_watch

#include "fetch_and_persist_quote.cpp" // fetch_and_persist_quote
#include "quote.h"                     // Alpaca::Quote
#include <iostream>                    // std::cout, std::endl, std::flush
#include <list>                        // std::list
#include <stdio.h>                     // printf, puts
#include <string>                      // std::string
#include <unistd.h>                    // usleep

void Alpaca::Quote::watch(const std::list<std::string> &symbols) {
  for (const std::string symbol : symbols) {
    fetch_and_persist_quote(symbol, true);
  }

  while (true) {
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
  }
}

#endif

#ifndef ALPACA__QUOTE_watch
#define ALPACA__QUOTE_watch

#include "fetch_and_persist_quote.cpp"        // fetch_and_persist_quote
#include "quote.h"                            // Alpaca::Quote
#include "set_and_persist_price_movement.cpp" // set_and_persist_price_movement
#include <string>                             // std::string
#include <unistd.h>                           // usleep
#include <vector>                             // std::vector

#include <iostream> // std::cout, std::endl, std::flush
#include <stdio.h>  // printf, puts

void Alpaca::Quote::watch(const std::vector<std::string> symbols) {
  while (true) {
    for (const std::string symbol : symbols) {
      std::cout << fmt.bold << fmt.cyan << fmt.underline;
      puts(symbol.c_str());
      std::cout << fmt.reset;

      fetch_and_persist_quote(symbol);

      std::cout << fmt.bold << fmt.cyan;
      puts("Fetched and Persisted Quote");
      std::cout << fmt.reset;

      set_and_persist_price_movement(symbol);

      std::cout << fmt.bold << fmt.cyan;
      puts("Set and Persisted Price Movement");
      std::cout << fmt.reset;
    }

    std::cout << std::flush;
    usleep(5e5);
  }
}

#endif

#ifndef ALPACA__QUOTE_watch
#define ALPACA__QUOTE_watch

#include "fetch_and_persist_quote.cpp"        // fetch_and_persist_quote
#include "quote.h"                            // Alpaca::Quote
#include "read_collection.cpp"                // read_collection
#include "read_price_movement.cpp"            // read_price_movement
#include "set_and_persist_price_movement.cpp" // set_and_persist_price_movement
#include <iostream> // std::cout, std::endl, std::flush
#include <stdio.h>  // printf, puts
#include <string>   // std::string
#include <unistd.h> // usleep
#include <vector>   // std::vector

void Alpaca::Quote::watch(const std::vector<std::string> symbols) {
  for (const std::string symbol : symbols) {
    read_collection(symbol);
    read_price_movement(symbol);
    fetch_and_persist_quote(symbol, true);
  }

  while (true) {
    for (const std::string symbol : symbols) {
      std::cout << fmt.bold << fmt.cyan << fmt.underline;
      puts(symbol.c_str());
      std::cout << fmt.reset;

      fetch_and_persist_quote(symbol);

      std::cout << fmt.bold << fmt.yellow;
      puts("Fetched and Persisted Quote");
      std::cout << fmt.reset;

      set_and_persist_price_movement(symbol);

      std::cout << fmt.bold << fmt.yellow;
      puts("Set and Persisted Price Movement");
      std::cout << fmt.reset << std::endl;
    }

    std::cout << fmt.bold << fmt.magenta;
    puts("================================");
    std::cout << fmt.reset << std::endl;

    std::cout << std::flush;
    usleep(5e5);
  }
}

#endif

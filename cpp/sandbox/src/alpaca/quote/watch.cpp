#ifndef ALPACA__QUOTE_watch
#define ALPACA__QUOTE_watch

#include "fetch_and_persist_quote.cpp" // fetch_and_persist_quote
#include "quote.h"                     // Alpaca::Quote
#include <string>                      // std::string
#include <unistd.h>                    // usleep
#include <vector>                      // std::vector

// TODO: Delete
#include <stdio.h> // printf

void Alpaca::Quote::watch(const std::vector<std::string> symbols) {
  while (true) {
    for (const std::string symbol : symbols) {
      printf("symbol: %s\n", symbol.c_str());
      fetch_and_persist_quote(symbol);
    }

    std::cout << std::flush;
    usleep(5e5);
  }
}

#endif

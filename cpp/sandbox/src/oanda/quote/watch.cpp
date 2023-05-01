#ifndef OANDA__QUOTE_watch
#define OANDA__QUOTE_watch

#include "fetch_and_persist_margin_rates.cpp" // fetch_and_persist_margin_rates
#include "fetch_and_persist_quote.cpp"        // fetch_and_persist_quote
#include "quote.h"                            // Oanda::Quote
#include <iostream> // std::cout, std::endl, std::flush
#include <list>     // std::list
#include <stdio.h>  // printf, puts
#include <string>   // std::string
#include <unistd.h> // usleep

void Oanda::Quote::watch(const std::list<std::string> &symbols) {
  for (const std::string symbol : symbols) {
    fetch_and_persist_quote(symbol, true);
  }

  fetch_and_persist_margin_rates(symbols);

  while (true) {
    for (const std::string symbol : symbols) {
      std::cout << fmt.bold << fmt.cyan << fmt.underline;
      puts(symbol.c_str());
      std::cout << fmt.reset;

      fetch_and_persist_quote(symbol);
    }

    std::cout << std::flush;
    usleep(5e5);
  }
}

#endif

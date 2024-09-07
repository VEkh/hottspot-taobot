#ifndef ALPACA__QUOTE_watch
#define ALPACA__QUOTE_watch

#include "fetch_and_persist_quote.cpp" // fetch_and_persist_quote
#include "quote.h"                     // Alpaca::Quote
#include <iostream>                    // std::cout, std::endl, std::flush
#include <list>                        // std::list
#include <stdio.h>                     // printf, puts
#include <string>                      // std::string
#include <time.h>                      // time
#include <unistd.h>                    // usleep

void Alpaca::Quote::watch(const std::list<std::string> &symbols) {
  const double now = time(nullptr);

  this->market_availability.set_market_close_epoch(now);
  this->market_availability.set_market_open_epoch(now, -30 * 60);

  bool is_market_open = this->market_availability.is_market_open(now);

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
    }

    std::cout << std::flush;
    usleep(5e5);

    is_market_open = this->market_availability.is_market_open(time(nullptr));
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("😴 Market is closed\n");
  std::cout << fmt.reset;
}

#endif

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

      std::cout << fmt.bold << fmt.yellow;
      puts("Fetched and Persisted Quote");
      std::cout << fmt.reset;
    }

    this->db_quote.insert_latest_avg_one_sec_variances();
    std::cout << fmt.bold << fmt.yellow;
    puts("Set and Persisted Price Movement");
    std::cout << fmt.reset << std::endl;

    std::cout << fmt.bold << fmt.magenta;
    puts("================================");
    std::cout << fmt.reset << std::endl;

    std::cout << std::flush;
    usleep(5e5);
  }
}

#endif

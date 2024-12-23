#ifndef OANDA__TAO_BOT_log_env_symbols
#define OANDA__TAO_BOT_log_env_symbols

#include "tao_bot.h" // Oanda::TaoBot, fmt
#include <iostream>  // std::cout, std::flush, std::endl
#include <list>      // std::list
#include <stdio.h>   // printf
#include <string>    // std::string

void Oanda::TaoBot::log_env_symbols() {
  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("Environment Symbols");
  std::cout << fmt.reset << std::endl;

  std::list<std::string>::iterator symbol_it;

  for (symbol_it = this->env_symbols.begin();
       symbol_it != this->env_symbols.end(); symbol_it++) {
    std::cout << fmt.bold;

    if (symbol_it != this->env_symbols.begin()) {
      printf(" ");
    }

    if (*symbol_it == this->symbol) {
      std::cout << fmt.green << fmt.underline;
    } else {
      std::cout << fmt.yellow;
    }

    printf("%s", symbol_it->c_str());

    std::cout << fmt.reset << std::flush;
  }

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif

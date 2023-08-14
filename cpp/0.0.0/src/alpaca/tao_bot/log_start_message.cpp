#ifndef ALPACA__TAO_BOT_log_start_message
#define ALPACA__TAO_BOT_log_start_message

#include "tao_bot.h" // Alpaca::TaoBot, fmt, quantity
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf

void Alpaca::TaoBot::log_start_message() {
  std::cout << fmt.bold << fmt.cyan;
  printf("Started TaoBot for ");

  std::cout << fmt.blue;
  printf("%s\n\n", this->symbol.c_str());

  std::cout << fmt.reset;
}

#endif

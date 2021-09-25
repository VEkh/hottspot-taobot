#ifndef OANDA__TAO_BOT_log_start_message
#define OANDA__TAO_BOT_log_start_message

#include "tao_bot.h" // Oanda::TaoBot, fmt, quantity
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf

void Oanda::TaoBot::log_start_message() {
  std::cout << fmt.bold << fmt.cyan;
  printf("Started TaoBot for ");

  std::cout << fmt.blue;
  printf("%s\n\n", this->symbol);

  std::cout << fmt.reset;
}

#endif

#ifndef ALPACA__TAO_BOT_log_price_action
#define ALPACA__TAO_BOT_log_price_action

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Alpaca::TaoBot, fmt
#include <iostream>          // std::cout, std::endl
#include <stdio.h>           // printf

void Alpaca::TaoBot::log_price_action() {
  if (!this->day_candle.open) {
    return;
  }

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("💥 Price Action\n");
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.yellow;
  printf("Current Price Range: %'.2f • %.2f%% of Open\n",
         this->day_candle.range(), this->day_candle.range_open_percent());
  std::cout << fmt.reset << std::endl;
}

#endif

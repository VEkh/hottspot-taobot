#ifndef OANDA__TAO_BOT_log_end_of_trading_period
#define OANDA__TAO_BOT_log_end_of_trading_period

#include "log_performance.cpp" // log_performance
#include "tao_bot.h"           // Oanda::TaoBot, fmt
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // printf

void Oanda::TaoBot::log_end_of_trading_period() {
  std::cout << fmt.bold << fmt.green << std::endl;
  printf("🎊 The market session is over! Hope you made some guap 🤑");
  std::cout << fmt.reset << std::endl;

  log_performance();
}

#endif

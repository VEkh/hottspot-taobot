#ifndef ALPACA__TAO_BOT_log_end_of_trading_period
#define ALPACA__TAO_BOT_log_end_of_trading_period

#include "log_performance.cpp" // log_performance
#include "tao_bot.h"           // Alpaca::TaoBot, fmt
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // puts

void Alpaca::TaoBot::log_end_of_trading_period() {
  std::cout << fmt.bold << fmt.green << std::endl;
  puts("🎊 The market session is over! Hope you made some guap 🤑");
  std::cout << fmt.reset;

  log_performance();
}

#endif

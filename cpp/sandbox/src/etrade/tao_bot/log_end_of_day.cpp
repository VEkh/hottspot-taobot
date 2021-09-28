#ifndef ETRADE__TAO_BOT_log_end_of_day
#define ETRADE__TAO_BOT_log_end_of_day

#include "log_performance.cpp" // log_performance
#include "tao_bot.h"           // ETrade::TaoBot, fmt
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // puts

void ETrade::TaoBot::log_end_of_day() {
  std::cout << fmt.bold << fmt.green << std::endl;
  puts("🎊 The day's over! Hope you made some guap 🤑");
  std::cout << fmt.reset;

  log_performance();
}

#endif

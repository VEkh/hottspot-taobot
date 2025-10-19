#ifndef OANDA__TAO_BOT_log_market_session_performance
#define OANDA__TAO_BOT_log_market_session_performance

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "tao_bot.h"             // Oanda::TaoBot
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Oanda::TaoBot::log_market_session_performance() {
  if (!this->market_session_performance.market_session_id) {
    return;
  }

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("📊 Market Session Performance\n");
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.yellow;
  printf("Current Drawdown: %.2f%% • Max Drawdown %.2f%% • Time to Max "
         "Drawdown: %s",
         this->market_session_performance.drawdown_percent,
         this->market_session_performance.max_drawdown_percent,
         ::utils::integer_::seconds_to_clock(
             this->market_session_performance.time_to_max_drawdown_seconds)
             .c_str());
  std::cout << fmt.reset << std::endl << std::endl;
}

#endif

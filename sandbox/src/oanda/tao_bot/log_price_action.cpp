#ifndef OANDA__TAO_BOT_log_price_action
#define OANDA__TAO_BOT_log_price_action

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Oanda::TaoBot, fmt
#include <iostream>          // std::cout, std::endl
#include <stdio.h>           // printf
#include <string>            // std::string

void Oanda::TaoBot::log_price_action() {
  if (!this->day_candle.open) {
    return;
  }

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("💥 Price Action (Range Open Percent)\n");
  std::cout << fmt.reset;

  const double current_range_open_percent =
      this->day_candle.range_open_percent();

  std::cout << fmt.bold << fmt.yellow;
  printf("Current: %.2f%%\n", current_range_open_percent);

  std::cout << fmt.reset << std::endl;
}

#endif

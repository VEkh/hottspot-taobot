#ifndef ALPACA__TAO_BOT_log_price_action
#define ALPACA__TAO_BOT_log_price_action

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Alpaca::TaoBot, fmt
#include <iostream>          // std::cout, std::endl
#include <stdio.h>           // printf
#include <string>            // std::string

void Alpaca::TaoBot::log_price_action() {
  if (!this->day_candle.open) {
    return;
  }

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("💥 Price Action (Range Open Percent)\n");
  std::cout << fmt.reset;

  const double current_range_open_percent =
      this->day_candle.range_open_percent();

  const double avg = this->price_action_stats.avg;
  const double std = this->price_action_stats.std;

  const double z_score =
      this->price_action_stats.z_score(current_range_open_percent);

  std::cout << fmt.bold << fmt.yellow;
  printf("Current: %.2f%% • μ: %.2f%% • σ: %.2f%% • Ζ: %+.2f\n",
         current_range_open_percent, avg, std, z_score);
  std::cout << fmt.reset << std::endl;
}

#endif

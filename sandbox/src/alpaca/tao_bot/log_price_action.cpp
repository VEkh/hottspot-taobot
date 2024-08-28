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

  const double avg = this->price_action_stats.avg;
  const double std = this->price_action_stats.std;

  const double current_range_open_percent =
      this->day_candle.range_open_percent();

  const double avg_delta_sigma_multiple =
      std ? (current_range_open_percent - avg) / std : 0;

  const int time_range_weeks =
      this->api_client.config.price_action_stats_time_range_weeks;

  const std::string time_range_text =
      time_range_weeks ? std::to_string(time_range_weeks) + "-Week"
                       : "All Time";

  std::cout << fmt.bold << fmt.yellow;
  printf("Current: %.2f%% (δμ/σ: %+.2f) • %s μ: %.2f%% • σ: %.2f%%\n",
         current_range_open_percent, avg_delta_sigma_multiple,
         time_range_text.c_str(), avg, std);
  std::cout << fmt.reset << std::endl;
}

#endif

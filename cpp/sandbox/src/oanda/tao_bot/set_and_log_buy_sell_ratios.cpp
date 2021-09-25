#ifndef OANDA__TAO_BOT_set_and_log_buy_sell_ratios
#define OANDA__TAO_BOT_set_and_log_buy_sell_ratios

#include "build_moving_buy_sell_ratio_average.cpp" // build_moving_buy_sell_ratio_average
#include "lib/formatted.cpp"                       // Formatted
#include "lib/utils/integer.cpp"                   // ::utils::integer_
#include "tao_bot.h"                               // Oanda::TaoBot, fmt
#include <iostream>                                // std::cout, std::endl
#include <stdio.h>                                 // printf, puts
#include <vector>                                  // std::vector

void Oanda::TaoBot::set_and_log_buy_sell_ratios() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = this->quotes.size();

  if (!ticks) {
    return;
  }

  int long_period_seconds = 5 * 60;
  int short_period_seconds = 3 * 60;
  std::vector<int> moving_average_periods = {
      short_period_seconds,
      long_period_seconds,
  };

  std::map<int, std::map<const char *, double>> average_buy_sell_ratios =
      build_moving_buy_sell_ratio_average(moving_average_periods);

  this->long_average_buy_sell_ratio =
      average_buy_sell_ratios[long_period_seconds]["buy"];
  this->long_average_sell_buy_ratio =
      average_buy_sell_ratios[long_period_seconds]["sell"];

  this->short_average_buy_sell_ratio =
      average_buy_sell_ratios[short_period_seconds]["buy"];
  this->short_average_sell_buy_ratio =
      average_buy_sell_ratios[short_period_seconds]["sell"];

  std::cout << fmt.bold << fmt.underline << fmt.cyan;
  puts("Average Buy-Sell Ratios");
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.cyan;
  printf("Buy Δ / Sell Δ => ");

  for (int i = 0, l = moving_average_periods.size(); i < l; i++) {
    int period = moving_average_periods[i];

    if (i > 0) {
      printf(" • ");
    }

    printf("%s: %.2f", ::utils::integer_::seconds_to_clock(period).c_str(),
           average_buy_sell_ratios[period]["buy"]);
  }

  std::cout << std::endl;
  printf("Sell Δ / Buy Δ => ");

  for (int i = 0, l = moving_average_periods.size(); i < l; i++) {
    int period = moving_average_periods[i];

    if (i > 0) {
      printf(" • ");
    }

    printf("%s: %.2f", ::utils::integer_::seconds_to_clock(period).c_str(),
           average_buy_sell_ratios[period]["sell"]);
  }

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif

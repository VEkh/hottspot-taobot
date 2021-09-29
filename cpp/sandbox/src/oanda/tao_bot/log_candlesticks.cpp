#ifndef OANDA__TAO_BOT_log_candlesticks
#define OANDA__TAO_BOT_log_candlesticks

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Oanda::TaoBot, fmt
#include <iostream>          // std::cout, std::endl
#include <stdio.h>           // printf

void Oanda::TaoBot::log_candlesticks() {
  if (!this->candlesticks.size()) {
    return;
  }

  std::list<candlestick_t>::iterator candlestick = this->candlesticks.begin();

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  puts("🍡 Candlesticks");

  std::cout << fmt.reset << fmt.bold << fmt.cyan;

  while (candlestick != this->candlesticks.end()) {
    const double profit = candlestick->close - candlestick->open;
    Formatted::Stream log_color = profit >= 0 ? fmt.green : fmt.red;

    std::cout << log_color;

    printf("⌚ %s: %+'.5f\n", candlestick->clock_time.c_str(), profit);

    candlestick++;
  }

  std::cout << std::endl << fmt.reset;
}

#endif

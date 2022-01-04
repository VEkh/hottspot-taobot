#ifndef ALPACA__TAO_BOT_log_candlesticks
#define ALPACA__TAO_BOT_log_candlesticks

#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // utils::float_
#include "tao_bot.h"           // Alpaca::TaoBot, fmt
#include <iostream>            // std::cout, std::endl
#include <list>                // std::list
#include <stdio.h>             // printf

void Alpaca::TaoBot::log_candlesticks() {
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

    printf("⌚ %s: %+'.2f\n", candlestick->clock_time.c_str(),
           ::utils::float_::to_currency(profit));

    candlestick++;
  }

  std::cout << std::endl << fmt.reset;
}

#endif

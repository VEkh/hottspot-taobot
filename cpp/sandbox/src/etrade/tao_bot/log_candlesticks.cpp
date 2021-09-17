#ifndef ETRADE__TAO_BOT_log_candlesticks
#define ETRADE__TAO_BOT_log_candlesticks

/*
 * ETrade::TaoBot
 * fmt
 * quote_t
 * quotes
 * symbol
 */
#include "tao_bot.h"

#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/float.cpp"   // utils::float_
#include "lib/utils/integer.cpp" // utils::integer_
#include <iomanip>               // std::setprecision
#include <iostream>              // std::cout, std::endl, std::fixed
#include <stdio.h>               // printf

void ETrade::TaoBot::log_candlesticks() {
  if (!this->candlesticks.size()) {
    return;
  }

  std::list<candlestick_t>::iterator candlestick = this->candlesticks.begin();

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  puts("🍡 Candlesticks");

  std::cout << fmt.reset << fmt.bold << fmt.cyan;

  puts("[\n");

  while (candlestick != this->candlesticks.end()) {
    const double profit = candlestick->close - candlestick->open;
    Formatted::Stream log_color = profit >= 0 ? fmt.green : fmt.red;

    std::cout << log_color;

    printf(" ⌚ %s: +/- %+'.2f • O: %'.2f • C: %'.2f • H: %'.2f • L: %'.2f\n",
           candlestick->clock_time.c_str(), utils::float_::to_currency(profit),
           utils::float_::to_currency(candlestick->open),
           utils::float_::to_currency(candlestick->close),
           utils::float_::to_currency(candlestick->high),
           utils::float_::to_currency(candlestick->low));

    candlestick++;
  }

  std::cout << fmt.cyan;
  puts("]\n");

  std::cout << fmt.reset;
}

#endif

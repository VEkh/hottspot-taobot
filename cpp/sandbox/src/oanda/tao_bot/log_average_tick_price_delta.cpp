#ifndef OANDA__TAO_BOT_log_average_tick_price_delta
#define OANDA__TAO_BOT_log_average_tick_price_delta

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "tao_bot.h"             // Oanda::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Oanda::TaoBot::log_average_tick_price_delta() {
  if (!this->average_tick_price_delta) {
    return;
  }

  std::cout << fmt.bold << fmt.underline << fmt.cyan;

  std::cout << "💲 Avg Tick Price Δ: ("
            << ::utils::integer_::seconds_to_clock(
                   this->AVERAGE_TICK_PRICE_DELTA_PERIOD)
            << ")";

  std::cout << fmt.reset << std::endl;
  std::cout << fmt.bold << fmt.cyan;

  printf("x10: %.5f • x%i: %.5f\n", this->average_tick_price_delta * 10.0,
         (int)this->MIN_TARGET_TICK_MOVEMENT,
         this->average_tick_price_delta * this->MIN_TARGET_TICK_MOVEMENT);

  std::cout << fmt.reset << std::endl;
}

#endif

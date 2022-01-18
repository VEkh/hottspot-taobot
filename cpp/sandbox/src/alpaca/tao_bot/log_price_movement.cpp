#ifndef ALPACA__TAO_BOT_log_price_movement
#define ALPACA__TAO_BOT_log_price_movement

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "tao_bot.h"             // Alpaca::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Alpaca::TaoBot::log_price_movement() {
  const double one_second_variance =
      this->price_movement.three_minute_one_second_variance.average;

  if (!one_second_variance) {
    return;
  }

  std::cout << fmt.bold << fmt.underline << fmt.cyan;

  std::cout << "💲 Avg Tick Price Δ: ("
            << ::utils::integer_::seconds_to_clock(
                   this->AVERAGE_TICK_PRICE_DELTA_PERIOD)
            << ")";

  std::cout << fmt.reset << std::endl;
  std::cout << fmt.bold << fmt.cyan;

  printf("x10: %.5f • x%i: %.5f\n", one_second_variance * 10.0,
         (int)this->MIN_TARGET_TICK_MOVEMENT,
         one_second_variance * this->MIN_TARGET_TICK_MOVEMENT);

  std::cout << fmt.reset << std::endl;
}

#endif

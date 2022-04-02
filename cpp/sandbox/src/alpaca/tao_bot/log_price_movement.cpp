#ifndef ALPACA__TAO_BOT_log_price_movement
#define ALPACA__TAO_BOT_log_price_movement

#include "lib/utils/integer.cpp"        // ::utils::integer_
#include "min_target_tick_movement.cpp" // min_target_tick_movement
#include "tao_bot.h"                    // Alpaca::TaoBot, fmt
#include <iostream>                     // std::cout, std::endl
#include <stdio.h>                      // printf

void Alpaca::TaoBot::log_price_movement() {
  const double one_second_variance =
      this->price_movement.three_minute_one_second_variance.average;

  if (!one_second_variance) {
    return;
  }

  const double min_target_tick_movement_ = min_target_tick_movement();

  const double short_term_one_second_variance =
      this->price_movement.short_term_three_minute_one_second_variance.average;

  std::cout << fmt.bold << fmt.underline << fmt.cyan;

  std::cout << "💲 Avg Tick Price Δ: ("
            << ::utils::integer_::seconds_to_clock(
                   this->AVERAGE_TICK_PRICE_DELTA_PERIOD)
            << ")";

  std::cout << fmt.reset << std::endl;
  std::cout << fmt.bold << fmt.cyan;

  printf("x1: %.5f • x%i: %.5f\n", one_second_variance,
         (int)min_target_tick_movement_,
         one_second_variance * min_target_tick_movement_);

  if (short_term_one_second_variance) {
    const double short_term_long_term_variance_percentage =
        100.0 * (short_term_one_second_variance / one_second_variance);

    printf("Short-Term One Second Variance: %.5f (%.3f%% Long-Term)\n",
           short_term_one_second_variance,
           short_term_long_term_variance_percentage);
  }

  std::cout << fmt.reset << std::endl;
}

#endif

#ifndef OANDA__TAO_BOT_log_price_movement
#define OANDA__TAO_BOT_log_price_movement

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "tao_bot.h"             // Oanda::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Oanda::TaoBot::log_price_movement() {
  const double one_second_variance =
      this->price_movement.three_minute_one_second_variance.average;

  if (!one_second_variance) {
    return;
  }

  const double short_term_one_second_variance =
      this->price_movement.short_term_three_minute_one_second_variance.average;

  std::cout << fmt.bold << fmt.underline << fmt.cyan;

  printf(
      "💲 %s Avg Tick Price Δ: (%s)\n", this->symbol.c_str(),
      ::utils::integer_::seconds_to_clock(this->AVG_ONE_SEC_VARIANCE_TIMEFRAME)
          .c_str());

  std::cout << fmt.reset << fmt.bold << fmt.cyan;

  printf("Long-Term One Second Variance: %.7f\n", one_second_variance);

  if (short_term_one_second_variance) {
    const double short_term_long_term_variance_percentage =
        100.0 * (short_term_one_second_variance / one_second_variance);

    printf("Short-Term One Second Variance: %.7f (%.3f%% Long-Term)\n",
           short_term_one_second_variance,
           short_term_long_term_variance_percentage);
  }

  std::cout << fmt.reset << std::endl;
}

#endif

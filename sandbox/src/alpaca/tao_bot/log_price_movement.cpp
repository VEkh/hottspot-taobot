#ifndef ALPACA__TAO_BOT_log_price_movement
#define ALPACA__TAO_BOT_log_price_movement

#include "lib/utils/integer.cpp"         // ::utils::integer_
#include "should_use_price_movement.cpp" // should_use_price_movement
#include "tao_bot.h"                     // Alpaca::TaoBot, fmt
#include <iostream>                      // std::cout, std::endl
#include <stdio.h>                       // printf

void Alpaca::TaoBot::log_price_movement() {
  if (!should_use_price_movement()) {
    return;
  }

  const double running_avg_one_sec_variance =
      this->avg_one_sec_variances.running;

  if (!running_avg_one_sec_variance) {
    return;
  }

  const double latest_avg_one_sec_variance = this->avg_one_sec_variances.latest;

  std::cout << fmt.bold << fmt.underline << fmt.cyan;

  printf(
      "💲 %s One Second Variance Averages (%s)\n", this->symbol.c_str(),
      ::utils::integer_::seconds_to_clock(this->AVG_ONE_SEC_VARIANCE_TIMEFRAME)
          .c_str());

  std::cout << fmt.reset << fmt.bold << fmt.cyan;

  if (latest_avg_one_sec_variance) {
    const double latest_to_running_percentage =
        100.0 * (latest_avg_one_sec_variance / running_avg_one_sec_variance);

    printf("Latest:  %.5f (%.3f%% Long-Term) %s\n", latest_avg_one_sec_variance,
           latest_to_running_percentage,
           latest_to_running_percentage > 100 ? "🥵" : "🥶");
  }

  printf("Running: %.5f\n", running_avg_one_sec_variance);

  std::cout << fmt.reset << std::endl;
}

#endif

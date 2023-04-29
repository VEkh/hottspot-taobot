#ifndef OANDA__TAO_BOT_log_price_movement
#define OANDA__TAO_BOT_log_price_movement

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "tao_bot.h"             // Oanda::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Oanda::TaoBot::log_price_movement() {
  const double running_one_sec_variance_avg =
      this->one_sec_variance_avgs.running;

  if (!running_one_sec_variance_avg) {
    return;
  }

  const double latest_one_sec_variance_avg = this->one_sec_variance_avgs.latest;

  std::cout << fmt.bold << fmt.underline << fmt.cyan;

  printf(
      "💲 %s One Second Variance Averages (%s)\n", this->symbol.c_str(),
      ::utils::integer_::seconds_to_clock(this->AVG_ONE_SEC_VARIANCE_TIMEFRAME)
          .c_str());

  std::cout << fmt.reset << fmt.bold << fmt.cyan;

  if (latest_one_sec_variance_avg) {
    const double latest_to_running_percentage =
        100.0 * (latest_one_sec_variance_avg / running_one_sec_variance_avg);

    printf("Latest:  %.7f (%.3f%% Long-Term) %s\n", latest_one_sec_variance_avg,
           latest_to_running_percentage,
           latest_to_running_percentage > 100 ? "🥵" : "🥶");
  }

  printf("Running: %.7f\n", running_one_sec_variance_avg);

  std::cout << fmt.reset << std::endl;
}

#endif

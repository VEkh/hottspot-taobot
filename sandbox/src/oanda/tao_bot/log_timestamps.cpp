#ifndef OANDA__TAO_BOT_log_timestamps
#define OANDA__TAO_BOT_log_timestamps

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/time.cpp"    // ::utils::time_
#include "runtime.cpp"           // runtime
#include "tao_bot.h"             // Oanda::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Oanda::TaoBot::log_timestamps() {
  std::cout << fmt.bold;

  std::cout << fmt.yellow;
  printf("⌚ Current Time:    %s • Runtime: %s",
         ::utils::time_::date_string(this->current_epoch, "%a, %b %d, %Y %X %Z",
                                     "America/Chicago")
             .c_str(),
         ::utils::integer_::seconds_to_clock(runtime()).c_str());
  std::cout << std::endl;

  std::cout << fmt.green;
  printf(
      "🚀 Market Open:     %s",
      ::utils::time_::date_string(this->market_availability.market_epochs.open,
                                  "%a, %b %d, %Y %X %Z", "America/Chicago")
          .c_str());
  std::cout << std::endl;

  std::cout << fmt.red;
  printf(
      "🏁 Market Close:    %s",
      ::utils::time_::date_string(this->market_availability.market_epochs.close,
                                  "%a, %b %d, %Y %X %Z", "America/Chicago")
          .c_str());
  std::cout << std::endl;

  if (this->backtest.is_active) {
    const long int backtest_duration =
        time(nullptr) - this->backtest.started_at;

    std::cout << fmt.cyan;
    printf("⌛ Backtest Start:  %s • Runtime: %s\n",
           ::utils::time_::date_string(this->backtest.config.start_epoch,
                                       "%a, %b %d, %Y %X %Z", "America/Chicago")
               .c_str(),
           ::utils::integer_::seconds_to_clock(backtest_duration).c_str());
  }

  std::cout << fmt.reset << std::endl;
}

#endif

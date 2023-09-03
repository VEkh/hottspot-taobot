#ifndef ALPACA__TAO_BOT_log_timestamps
#define ALPACA__TAO_BOT_log_timestamps

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/time.cpp"    // ::utils::time_
#include "runtime.cpp"           // runtime
#include "tao_bot.h"             // Alpaca::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf, snprintf
#include <string.h>              // strlen
#include <string>                // std::string
#include <time.h>                // time

void Alpaca::TaoBot::log_timestamps() {
  std::cout << fmt.bold << fmt.cyan;

  printf("⌚ Current Time: %s • Runtime: %s\n",
         ::utils::time_::date_string(this->current_epoch, "%a, %b %d, %Y %X %Z",
                                     "America/Chicago")
             .c_str(),
         ::utils::integer_::seconds_to_clock(runtime()).c_str());

  if (this->backtest.is_active) {
    const long int backtest_duration =
        time(nullptr) - this->backtest.started_at;

    printf("⌛ Backtest Start Epoch: %s • Runtime: %s\n",
           ::utils::time_::date_string(this->backtest.config.start_epoch,
                                       "%a, %b %d, %Y %X %Z", "America/Chicago")
               .c_str(),
           ::utils::integer_::seconds_to_clock(backtest_duration).c_str());
  }

  std::cout << fmt.reset << std::endl;
}

#endif

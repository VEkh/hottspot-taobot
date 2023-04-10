#ifndef ALPACA__TAO_BOT_log_timestamps
#define ALPACA__TAO_BOT_log_timestamps

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/time.cpp"    // ::utils::time_
#include "runtime.cpp"           // runtime
#include "tao_bot.h"             // Alpaca::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Alpaca::TaoBot::log_timestamps() {
  std::cout << fmt.bold << fmt.cyan;
  printf("⌚ Current Time: %s • Runtime: %s\n",
         ::utils::time_::date_string(this->api_client.config.current_epoch,
                                     "%a, %b %d, %Y %X %Z", "America/Chicago")
             .c_str(),
         ::utils::integer_::seconds_to_clock(runtime()).c_str());
  std::cout << fmt.reset << std::endl;
}

#endif

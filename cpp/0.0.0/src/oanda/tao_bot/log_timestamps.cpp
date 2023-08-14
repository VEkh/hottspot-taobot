#ifndef OANDA__TAO_BOT_log_timestamps
#define OANDA__TAO_BOT_log_timestamps

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/time.cpp"    // ::utils::time_
#include "runtime.cpp"           // runtime
#include "tao_bot.h"             // Oanda::TaoBot, fmt
#include <ctime>                 // std::time, std::time_t
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Oanda::TaoBot::log_timestamps() {
  std::time_t now = std::time(nullptr);

  std::cout << fmt.bold << fmt.cyan;
  printf(
      "⌚ Current Time: %s • Runtime: %s\n",
      ::utils::time_::date_string(now, "%a, %b %d, %Y %X %Z", "America/Chicago")
          .c_str(),
      ::utils::integer_::seconds_to_clock(runtime()).c_str());
  std::cout << fmt.reset << std::endl;
}

#endif

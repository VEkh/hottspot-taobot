#ifndef ALPACA__TAO_BOT_is_holiday
#define ALPACA__TAO_BOT_is_holiday

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, fmt
#include <ctime>              // std::time, std::time_t
#include <map>                // std::map
#include <string>             // std::string

bool Alpaca::TaoBot::is_holiday() {
  std::map<std::string, bool> HOLIDAYS = {
      {"2023-01-02", true}, {"2023-01-16", true}, {"2023-02-20", true},
      {"2023-04-07", true}, {"2023-05-29", true}, {"2023-06-19", true},
      {"2023-07-04", true}, {"2023-09-04", true}, {"2023-11-23", true},
      {"2023-12-25", true},
  };

  std::time_t now = std::time(nullptr);
  const std::string date_string = ::utils::time_::date_string(now);

  return HOLIDAYS[date_string];
}

#endif

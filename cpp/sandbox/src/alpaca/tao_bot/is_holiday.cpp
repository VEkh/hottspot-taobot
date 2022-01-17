#ifndef ALPACA__TAO_BOT_is_holiday
#define ALPACA__TAO_BOT_is_holiday

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, fmt
#include <ctime>              // std::time, std::time_t
#include <map>                // std::map
#include <string>             // std::string

bool Alpaca::TaoBot::is_holiday() {
  std::map<std::string, bool> HOLIDAYS = {
      {"2022-01-17", true}, {"2022-02-21", true}, {"2022-04-15", true},
      {"2022-05-30", true}, {"2022-06-20", true}, {"2022-07-04", true},
      {"2022-09-05", true}, {"2022-11-24", true}, {"2022-12-26", true},
  };

  std::time_t now = std::time(nullptr);
  const std::string date_string = ::utils::time_::date_string(&now);

  return HOLIDAYS[date_string];
}

#endif

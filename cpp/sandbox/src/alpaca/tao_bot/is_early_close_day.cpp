#ifndef ALPACA__TAO_BOT_is_early_close_day
#define ALPACA__TAO_BOT_is_early_close_day

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, fmt
#include <ctime>              // std::time, std::time_t
#include <map>                // std::map
#include <string>             // std::string

bool Alpaca::TaoBot::is_early_close_day() {
  std::map<std::string, bool> DATES = {
      {"2022-07-03", true},
      {"2022-11-25", true},
  };

  std::time_t now = std::time(nullptr);
  const std::string date_string = ::utils::time_::date_string(now);

  return DATES[date_string];
}

#endif

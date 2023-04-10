#ifndef ALPACA__TAO_BOT_is_early_close_day
#define ALPACA__TAO_BOT_is_early_close_day

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, fmt
#include <map>                // std::map
#include <string>             // std::string

bool Alpaca::TaoBot::is_early_close_day() {
  std::map<std::string, bool> DATES = {
      {"2023-07-03", true},
      {"2023-11-24", true},
  };

  const std::string date_string =
      ::utils::time_::date_string(this->api_client.config.current_epoch);

  return DATES[date_string];
}

#endif

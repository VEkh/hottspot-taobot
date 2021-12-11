#ifndef OANDA__TAO_BOT_is_market_open
#define OANDA__TAO_BOT_is_market_open

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Oanda::TaoBot

bool Oanda::TaoBot::is_market_open() {
  int day_of_week_ = ::utils::time_::day_of_week();

  if (day_of_week_ == 0) {
    return ::utils::time_::is_at_least({17, 0});
  }

  if (day_of_week_ == 5) {
    return ::utils::time_::is_before({17, 0});
  }

  return day_of_week_ != 6;
}

#endif

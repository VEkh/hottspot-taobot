#ifndef ALPACA__TAO_BOT_is_market_day
#define ALPACA__TAO_BOT_is_market_day

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

bool Alpaca::TaoBot::is_market_day() {
  const int day_of_week_ = ::utils::time_::day_of_week(this->current_epoch);

  return day_of_week_ >= 1 && day_of_week_ <= 5;
}

#endif

#ifndef ALPACA__TAO_BOT_is_market_open
#define ALPACA__TAO_BOT_is_market_open

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

bool Alpaca::TaoBot::is_market_open() {
  const int day_of_week_ = ::utils::time_::day_of_week(this->current_epoch);

  if (day_of_week_ < 1 || day_of_week_ > 5) {
    return false;
  }

  return ::utils::time_::is_at_least(this->current_epoch, {9, 30}) &&
         ::utils::time_::is_before(this->current_epoch, {16, 0});
}

#endif

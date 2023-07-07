#ifndef ALPACA__TAO_BOT_is_market_open
#define ALPACA__TAO_BOT_is_market_open

#include "is_market_day.cpp"  // is_market_day
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

#include <vector> // std::vector

bool Alpaca::TaoBot::is_market_open() {
  const int day_of_week_ = ::utils::time_::day_of_week(this->current_epoch);

  if (day_of_week_ < 1 || day_of_week_ > 5) {
    return false;
  }

  if (!is_market_day()) {
    return false;
  }

  if (is_holiday()) {
    return false;
  }

  std::vector<int> market_open_time = {9, 30};

  if (this->backtest.is_active && this->backtest.config.is_late_start) {
    market_open_time = {10, 0};
  }

  return ::utils::time_::is_at_least(this->current_epoch, market_open_time) &&
         ::utils::time_::is_before(this->current_epoch, {16, 0});
}

#endif

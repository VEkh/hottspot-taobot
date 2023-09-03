#ifndef ALPACA__TAO_BOT_is_end_of_trading_period
#define ALPACA__TAO_BOT_is_end_of_trading_period

#include "is_early_close_day.cpp" // is_early_close_day
#include "lib/utils/time.cpp"     // ::utils::time_
#include "tao_bot.h"              // Alpaca::TaoBot

bool Alpaca::TaoBot::is_end_of_trading_period() {
  if (is_early_close_day()) {
    return ::utils::time_::is_at_least(this->current_epoch,
                                       {
                                           .tm_sec = 0,
                                           .tm_min = 59,
                                           .tm_hour = 11,
                                       },
                                       "America/Chicago");
  }

  return ::utils::time_::is_at_least(this->current_epoch,
                                     {
                                         .tm_sec = 0,
                                         .tm_min = 59,
                                         .tm_hour = 14,
                                     },
                                     "America/Chicago");
}

#endif

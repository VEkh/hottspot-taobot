#ifndef OANDA__TAO_BOT_is_end_of_trading_period
#define OANDA__TAO_BOT_is_end_of_trading_period

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Oanda::TaoBot

bool Oanda::TaoBot::is_end_of_trading_period() {
  return ::utils::time_::day_of_week() == 5 &&
         ::utils::time_::is_at_least({
             .tm_sec = 0,
             .tm_min = 57,
             .tm_hour = 16,
         }) &&
         ::utils::time_::is_before({
             .tm_sec = 0,
             .tm_min = 0,
             .tm_hour = 17,
         });
}

#endif

#ifndef ALPACA__TAO_BOT_is_end_of_trading_period
#define ALPACA__TAO_BOT_is_end_of_trading_period

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

bool Alpaca::TaoBot::is_end_of_trading_period() {
  return ::utils::time_::is_at_least({15, 59}) &&
         ::utils::time_::is_before({16, 0});
}

#endif

#ifndef ALPACA__TAO_BOT_is_end_of_trading_period
#define ALPACA__TAO_BOT_is_end_of_trading_period

#include "is_early_close_day.cpp" // is_early_close_day
#include "lib/utils/time.cpp"     // ::utils::time_
#include "tao_bot.h"              // Alpaca::TaoBot

bool Alpaca::TaoBot::is_end_of_trading_period() {
  const double current_epoch = this->api_client.config.current_epoch;

  if (is_early_close_day()) {
    return ::utils::time_::is_at_least(current_epoch, {11, 59},
                                       "America/Chicago");
  }

  return ::utils::time_::is_at_least(current_epoch, {14, 59},
                                     "America/Chicago");
}

#endif

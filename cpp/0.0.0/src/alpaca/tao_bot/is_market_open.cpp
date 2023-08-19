#ifndef ALPACA__TAO_BOT_is_market_open
#define ALPACA__TAO_BOT_is_market_open

#include "is_market_day.cpp"  // is_market_day
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot
#include <time.h>             // tm

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

  tm market_open_time = {
      .tm_sec = 0,
      .tm_min = 30,
      .tm_hour = 9,
  };

  if (this->api_client.config.api_key == "live-alpha") {
    market_open_time = {
        .tm_sec = 25,
        .tm_min = 30,
        .tm_hour = 9,
    };
  } else if (this->backtest.is_active &&
             this->backtest.config.late_start_seconds) {
    market_open_time = {
        .tm_sec = this->backtest.config.late_start_seconds,
        .tm_min = 30,
        .tm_hour = 9,
    };
  }

  return ::utils::time_::is_at_least(this->current_epoch, market_open_time) &&
         ::utils::time_::is_before(this->current_epoch, {
                                                            .tm_sec = 0,
                                                            .tm_min = 0,
                                                            .tm_hour = 16,
                                                        });
}

#endif
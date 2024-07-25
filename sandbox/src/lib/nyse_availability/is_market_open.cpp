#ifndef NYSE_AVAILABILITY_is_market_open
#define NYSE_AVAILABILITY_is_market_open

#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "is_market_day.cpp"            // is_market_day
#include "lib/utils/time.cpp"           // ::utils::time_
#include "nyse_availability.h"          // NyseAvailability
#include <time.h>                       // tm

bool NyseAvailability::is_market_open(const double epoch,
                                      const int late_start_seconds = 0) {
  if (!is_market_day(epoch)) {
    return false;
  }

  if (is_end_of_trading_period(epoch)) {
    return false;
  }

  const tm market_open_time = {
      .tm_sec = late_start_seconds,
      .tm_min = 30,
      .tm_hour = 8,
  };

  return ::utils::time_::is_at_least(epoch, market_open_time,
                                     "America/Chicago") &&
         ::utils::time_::is_before(epoch,
                                   {
                                       .tm_sec = 0,
                                       .tm_min = 0,
                                       .tm_hour = 15,
                                   },
                                   "America/Chicago");
}

#endif

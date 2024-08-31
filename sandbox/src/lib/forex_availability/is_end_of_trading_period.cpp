#ifndef FOREX_AVAILABILITY_is_end_of_trading_period
#define FOREX_AVAILABILITY_is_end_of_trading_period

#include "forex_availability.h" // ForexAvailability
#include "lib/utils/time.cpp"   // ::utils::time_

bool ForexAvailability::is_end_of_trading_period(const double epoch) {
  if (::utils::time_::day_of_week(epoch) != 5) {
    return false;
  }

  return ::utils::time_::is_at_least(epoch,
                                     {
                                         .tm_sec = 0,
                                         .tm_min = 59,
                                         .tm_hour = 15,
                                     },
                                     "America/Chicago");
}

#endif

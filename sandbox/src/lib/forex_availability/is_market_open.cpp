#ifndef FOREX_AVAILABILITY_is_market_open
#define FOREX_AVAILABILITY_is_market_open

#include "forex_availability.h" // ForexAvailability
#include "lib/utils/time.cpp"   // ::utils::time_
#include <time.h>               // tm

bool ForexAvailability::is_market_open(const double epoch) {
  int day_of_week = ::utils::time_::day_of_week(epoch);

  if (day_of_week == 0) {
    return ::utils::time_::is_at_least(epoch,
                                       {
                                           .tm_sec = 0,
                                           .tm_min = 0,
                                           .tm_hour = 16,
                                       },
                                       "America/Chicago");
  }

  if (day_of_week == 5) {
    return ::utils::time_::is_before(epoch,
                                     {
                                         .tm_sec = 0,
                                         .tm_min = 0,
                                         .tm_hour = 16,
                                     },
                                     "America/Chicago");
  }

  return day_of_week != 6;
}

#endif

#ifndef NYSE_AVAILABILITY_is_end_of_trading_period
#define NYSE_AVAILABILITY_is_end_of_trading_period

#include "is_early_close_day.cpp" // is_early_close_day
#include "lib/utils/time.cpp"     // ::utils::time_
#include "nyse_availability.h"    // NyseAvailability

bool NyseAvailability::is_end_of_trading_period(const double epoch) {
  if (is_early_close_day(epoch)) {
    return ::utils::time_::is_at_least(epoch,
                                       {
                                           .tm_sec = 0,
                                           .tm_min = 59,
                                           .tm_hour = 11,
                                       },
                                       "America/Chicago");
  }

  return ::utils::time_::is_at_least(epoch,
                                     {
                                         .tm_sec = 0,
                                         .tm_min = 59,
                                         .tm_hour = 14,
                                     },
                                     "America/Chicago");
}

#endif

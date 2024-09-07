#ifndef FOREX_AVAILABILITY_is_market_day
#define FOREX_AVAILABILITY_is_market_day

#include "forex_availability.h"  // ForexAvailability
#include "is_in_date_lookup.cpp" // is_in_date_lookup
#include "lib/utils/time.cpp"    // ::utils::time_

bool ForexAvailability::is_market_day(const double epoch) {
  if (is_in_date_lookup(this->bad_data, epoch)) {
    return false;
  }

  const int day_of_week = ::utils::time_::day_of_week(epoch);

  return day_of_week != 6;
}

#endif

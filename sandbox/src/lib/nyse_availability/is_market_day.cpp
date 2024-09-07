#ifndef NYSE_AVAILABILITY_is_market_day
#define NYSE_AVAILABILITY_is_market_day

#include "is_holiday.cpp"            // is_holiday
#include "is_in_date_lookup.cpp"     // is_in_date_lookup
#include "is_market_day_of_week.cpp" // is_market_day_of_week
#include "nyse_availability.h"       // NyseAvailability

bool NyseAvailability::is_market_day(const double epoch) {
  if (!is_market_day_of_week(epoch)) {
    return false;
  }

  if (is_in_date_lookup(this->bad_data, epoch)) {
    return false;
  }

  if (is_holiday(epoch)) {
    return false;
  }

  return true;
}

#endif

#ifndef FOREX_AVAILABILITY_is_holiday
#define FOREX_AVAILABILITY_is_holiday

#include "forex_availability.h"  // ForexAvailability
#include "is_in_date_lookup.cpp" // is_in_date_lookup

bool ForexAvailability::is_holiday(const double epoch) {
  return is_in_date_lookup(this->holidays, epoch);
}

#endif

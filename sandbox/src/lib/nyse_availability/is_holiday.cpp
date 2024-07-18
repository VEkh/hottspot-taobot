#ifndef NYSE_AVAILABILITY_is_holiday
#define NYSE_AVAILABILITY_is_holiday

#include "is_in_date_lookup.cpp" // is_in_date_lookup
#include "nyse_availability.h"   // NyseAvailability

bool NyseAvailability::is_holiday(const double epoch) {
  return is_in_date_lookup(this->holidays, epoch);
}

#endif

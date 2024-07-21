#ifndef NYSE_AVAILABILITY_is_early_close_day
#define NYSE_AVAILABILITY_is_early_close_day

#include "is_in_date_lookup.cpp" // is_in_date_lookup
#include "nyse_availability.h"   // NyseAvailability

bool NyseAvailability::is_early_close_day(const double epoch) {
  return is_in_date_lookup(this->early_closes, epoch);
}

#endif

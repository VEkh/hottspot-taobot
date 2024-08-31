#ifndef FOREX_AVAILABILITY_is_in_date_lookup
#define FOREX_AVAILABILITY_is_in_date_lookup

#include "forex_availability.h" // ForexAvailability
#include "lib/utils/time.cpp"   // ::utils::time_
#include <string>               // std::string

bool ForexAvailability::is_in_date_lookup(std::map<std::string, bool> lookup,
                                          const double epoch) {
  const std::string date_string = ::utils::time_::date_string(epoch);

  return lookup[date_string];
}

#endif

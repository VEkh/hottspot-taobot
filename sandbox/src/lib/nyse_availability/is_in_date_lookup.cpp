#ifndef NYSE_AVAILABILITY_is_in_date_lookup
#define NYSE_AVAILABILITY_is_in_date_lookup

#include "lib/utils/time.cpp"  // ::utils::time_
#include "nyse_availability.h" // NyseAvailability
#include <string>              // std::string

bool NyseAvailability::is_in_date_lookup(std::map<std::string, bool> lookup,
                                         const double epoch) {
  const std::string date_string = ::utils::time_::date_string(epoch);

  return lookup[date_string];
}

#endif

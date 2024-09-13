#ifndef MARKET_AVAILABILITY__BASE_is_in_date_lookup
#define MARKET_AVAILABILITY__BASE_is_in_date_lookup

#include "base.h"             // MarketAvailability::Base
#include "lib/utils/time.cpp" // ::utils::time_
#include <string>             // std::string

bool MarketAvailability::Base::is_in_date_lookup(
    std::map<std::string, bool> lookup, const double epoch) {
  const std::string date_string = ::utils::time_::date_string(epoch);

  return lookup[date_string];
}

#endif

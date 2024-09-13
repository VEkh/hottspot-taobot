#ifndef MARKET_AVAILABILITY__BASE_is_holiday
#define MARKET_AVAILABILITY__BASE_is_holiday

#include "base.h"                // MarketAvailability::Base
#include "is_in_date_lookup.cpp" // is_in_date_lookup

bool MarketAvailability::Base::is_holiday(const double epoch) {
  return is_in_date_lookup(this->holidays, epoch);
}

#endif

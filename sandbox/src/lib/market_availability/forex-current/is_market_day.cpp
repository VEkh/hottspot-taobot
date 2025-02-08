#ifndef MARKET_AVAILABILITY__FOREX_is_market_day
#define MARKET_AVAILABILITY__FOREX_is_market_day

#include "forex.h"            // MarketAvailability::Forex, is_in_date_lookup
#include "lib/utils/time.cpp" // ::utils::time_

bool MarketAvailability::Forex::is_market_day(const double epoch) {
  if (is_in_date_lookup(this->bad_data, epoch)) {
    return false;
  }

  const int day_of_week = ::utils::time_::day_of_week(epoch);

  return day_of_week != 6;
}

#endif

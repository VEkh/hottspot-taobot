#ifndef MARKET_AVAILABILITY__NYSE_is_market_day_of_week
#define MARKET_AVAILABILITY__NYSE_is_market_day_of_week

#include "lib/utils/time.cpp" // ::utils::time_
#include "nyse.h"             // MarketAvailability::Nyse

bool MarketAvailability::Nyse::is_market_day_of_week(const double epoch) {
  const int day_of_week = ::utils::time_::day_of_week(epoch);

  return day_of_week >= 1 && day_of_week <= 5;
}

#endif

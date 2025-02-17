#ifndef MARKET_AVAILABILITY__FOREX_next_market_open_epoch
#define MARKET_AVAILABILITY__FOREX_next_market_open_epoch

#include "forex.h"                     // MarketAvailability::Forex
#include "lib/utils/time.cpp"          // ::utils::time_
#include "week_market_bound_epoch.cpp" // week_market_bound_epoch

double MarketAvailability::Forex::next_market_open_epoch(const double epoch) {
  const int day_of_week = ::utils::time_::day_of_week(epoch);

  if (day_of_week == 5 && epoch == week_market_bound_epoch(epoch, 5)) {
    return week_market_bound_epoch(epoch + 2 * this->ONE_DAY_SECONDS, 0);
  }

  if (day_of_week == 6) {
    return week_market_bound_epoch(epoch + this->ONE_DAY_SECONDS, 0);
  }

  return epoch;
}

#endif

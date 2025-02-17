#ifndef MARKET_AVAILABILITY__FOREX_seconds_since_first_open_of_week
#define MARKET_AVAILABILITY__FOREX_seconds_since_first_open_of_week

#include "forex.h"                     // MarketAvailability::Forex
#include "week_market_bound_epoch.cpp" // week_market_bound_epoch

double MarketAvailability::Forex::seconds_since_first_open_of_week(
    const double epoch, const int sessions_offset = 0) {
  const double first_market_open = week_market_bound_epoch(epoch, 0);

  const double epoch_seconds_since_first_open = epoch - first_market_open;

  const int sessions_since_first_open =
      (epoch_seconds_since_first_open / this->ONE_HOUR_SECONDS) /
      this->MARKET_DURATION_HOURS;

  return (sessions_since_first_open + sessions_offset) *
         this->MARKET_DURATION_HOURS * this->ONE_HOUR_SECONDS;
}

#endif

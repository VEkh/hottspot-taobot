#ifndef MARKET_AVAILABILITY__FOREX_set_market_close_epoch
#define MARKET_AVAILABILITY__FOREX_set_market_close_epoch

#include "forex.h"                              // MarketAvailability::Forex
#include "lib/utils/time.cpp"                   // ::utils::time_
#include "seconds_since_first_open_of_week.cpp" // seconds_since_first_open_of_week
#include "week_market_bound_epoch.cpp"          // week_market_bound_epoch

void MarketAvailability::Forex::set_market_close_epoch(const double epoch) {
  const double day_of_week = ::utils::time_::day_of_week(epoch);

  if (day_of_week == 6) {
    this->market_epochs.close = epoch;
    return;
  }

  const double close_epoch = week_market_bound_epoch(epoch, 0) +
                             seconds_since_first_open_of_week(epoch, 1);

  const double last_close_of_week = week_market_bound_epoch(epoch, 5);

  this->market_epochs.close = std::min(close_epoch, last_close_of_week);
}

#endif

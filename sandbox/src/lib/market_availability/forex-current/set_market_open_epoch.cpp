#ifndef MARKET_AVAILABILITY__FOREX_set_market_open_epoch
#define MARKET_AVAILABILITY__FOREX_set_market_open_epoch

#include "forex.h"                              // MarketAvailability::Forex
#include "seconds_since_first_open_of_week.cpp" // seconds_since_first_open_of_week
#include "week_market_bound_epoch.cpp"          // week_market_bound_epoch

void MarketAvailability::Forex::set_market_open_epoch(const double epoch) {
  this->market_epochs.open = week_market_bound_epoch(epoch, 0) +
                             seconds_since_first_open_of_week(epoch);
}

#endif

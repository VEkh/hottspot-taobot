#ifndef MARKET_AVAILABILITY__FOREX_set_market_open_epoch
#define MARKET_AVAILABILITY__FOREX_set_market_open_epoch

#include "forex.h"                   // MarketAvailability::Forex
#include "get_market_open_epoch.cpp" // get_market_open_epoch

void MarketAvailability::Forex::set_market_open_epoch(const double epoch) {
  const double today_market_open_epoch = get_market_open_epoch(epoch);
  const double yesterday_market_open_epoch =
      get_market_open_epoch(epoch - this->ONE_DAY_SECONDS);

  this->market_epochs.open = epoch < today_market_open_epoch
                                 ? yesterday_market_open_epoch
                                 : today_market_open_epoch;
}

// TODO: Decide
#include "seconds_since_first_open_of_week.cpp" // seconds_since_first_open_of_week
#include "week_market_bound_epoch.cpp"          // week_market_bound_epoch

void MarketAvailability::Forex::set_market_open_epoch(
    const double epoch, const int market_duration_hours) {
  this->market_epochs.open =
      week_market_bound_epoch(epoch, 0) +
      seconds_since_first_open_of_week(epoch, market_duration_hours);
}

#endif

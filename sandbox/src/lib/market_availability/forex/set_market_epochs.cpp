#ifndef MARKET_AVAILABILITY__FOREX_set_market_epochs
#define MARKET_AVAILABILITY__FOREX_set_market_epochs

#include "forex.h"                    // MarketAvailability::Forex
#include "set_market_close_epoch.cpp" // set_market_close_epoch
#include "set_market_open_epoch.cpp"  // set_market_open_epoch
#include <string>                     // std::string

void MarketAvailability::Forex::set_market_epochs(
    const double epoch, const int market_duration_hours,
    const std::string standard_open_time) {
  // TODO: Decide
  if (market_duration_hours) {
    set_market_close_epoch(epoch, market_duration_hours);
    set_market_open_epoch(epoch, market_duration_hours);

    return;
  }

  set_market_close_epoch(epoch, standard_open_time);
  set_market_open_epoch(epoch, standard_open_time);
}

#endif

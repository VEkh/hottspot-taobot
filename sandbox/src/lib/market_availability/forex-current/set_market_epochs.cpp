#ifndef MARKET_AVAILABILITY__FOREX_set_market_epochs
#define MARKET_AVAILABILITY__FOREX_set_market_epochs

#include "forex.h"                    // MarketAvailability::Forex
#include "set_market_close_epoch.cpp" // set_market_close_epoch
#include "set_market_open_epoch.cpp"  // set_market_open_epoch

void MarketAvailability::Forex::set_market_epochs(const double epoch) {
  set_market_close_epoch(epoch);
  set_market_open_epoch(epoch);
}

#endif

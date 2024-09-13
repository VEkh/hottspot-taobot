#ifndef MARKET_AVAILABILITY__NYSE_set_market_epochs
#define MARKET_AVAILABILITY__NYSE_set_market_epochs

#include "nyse.h"                     // MarketAvailability::Nyse
#include "set_market_close_epoch.cpp" // set_market_close_epoch
#include "set_market_open_epoch.cpp"  // set_market_open_epoch

void MarketAvailability::Nyse::set_market_epochs(const double epoch) {
  set_market_close_epoch(epoch);
  set_market_open_epoch(epoch);
  this->market_epochs.pre = this->market_epochs.open - (30 * 60);
}

#endif

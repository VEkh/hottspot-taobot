#ifndef FOREX_AVAILABILITY_set_market_epochs
#define FOREX_AVAILABILITY_set_market_epochs

#include "forex_availability.h"       // ForexAvailability
#include "set_market_close_epoch.cpp" // set_market_close_epoch
#include "set_market_open_epoch.cpp"  // set_market_open_epoch

void ForexAvailability::set_market_epochs(const double epoch) {
  set_market_close_epoch(epoch);
  set_market_open_epoch(epoch);
}

#endif

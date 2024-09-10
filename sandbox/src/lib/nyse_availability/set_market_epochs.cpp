#ifndef NYSE_AVAILABILITY_set_market_epochs
#define NYSE_AVAILABILITY_set_market_epochs

#include "nyse_availability.h"        // NyseAvailability
#include "set_market_close_epoch.cpp" // set_market_close_epoch
#include "set_market_open_epoch.cpp"  // set_market_open_epoch

void NyseAvailability::set_market_epochs(const double epoch) {
  set_market_close_epoch(epoch);
  set_market_open_epoch(epoch);
  this->market_epochs.pre = this->market_epochs.open - (30 * 60);
}

#endif

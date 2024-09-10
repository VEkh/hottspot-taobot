#ifndef NYSE_AVAILABILITY_set_market_open_epoch
#define NYSE_AVAILABILITY_set_market_open_epoch

#include "get_market_open_epoch.cpp" // get_market_open_epoch
#include "nyse_availability.h"       // NyseAvailability

void NyseAvailability::set_market_open_epoch(const double epoch,
                                             const int offset = 0) {
  this->market_epochs.open = get_market_open_epoch(epoch, offset);
}

#endif

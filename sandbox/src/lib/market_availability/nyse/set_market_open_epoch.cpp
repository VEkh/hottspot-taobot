#ifndef MARKET_AVAILABILITY__NYSE_set_market_open_epoch
#define MARKET_AVAILABILITY__NYSE_set_market_open_epoch

#include "get_market_open_epoch.cpp" // get_market_open_epoch
#include "nyse.h"                    // MarketAvailability::Nyse

void MarketAvailability::Nyse::set_market_open_epoch(const double epoch,
                                                     const int offset = 0) {
  this->market_epochs.open = get_market_open_epoch(epoch, offset);
}

#endif

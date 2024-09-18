#ifndef MARKET_AVAILABILITY__NYSE_next_market_open_epoch
#define MARKET_AVAILABILITY__NYSE_next_market_open_epoch

#include "get_market_open_epoch.cpp" // get_market_open_epoch
#include "nyse.h"                    // MarketAvailability::Nyse

double MarketAvailability::Nyse::next_market_open_epoch(const double epoch) {
  return get_market_open_epoch(epoch + this->ONE_DAY_SECONDS);
}

#endif

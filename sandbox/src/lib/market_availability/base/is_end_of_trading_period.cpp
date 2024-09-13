#ifndef MARKET_AVAILABILITY__BASE_is_end_of_trading_period
#define MARKET_AVAILABILITY__BASE_is_end_of_trading_period

#include "base.h" // MarketAvailability::Base

bool MarketAvailability::Base::is_end_of_trading_period(const double epoch) {
  return epoch >= this->market_epochs.close - 60;
}

#endif

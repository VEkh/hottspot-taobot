#ifndef MARKET_AVAILABILITY__FOREX_is_market_open
#define MARKET_AVAILABILITY__FOREX_is_market_open

#include "forex.h" // MarketAvailability::Forex, is_end_of_trading_period
#include "is_market_day.cpp" // is_market_day

bool MarketAvailability::Forex::is_market_open(const double epoch) {
  if (!is_market_day(epoch)) {
    return false;
  }

  if (is_end_of_trading_period(epoch)) {
    return false;
  }

  return epoch >= this->market_epochs.open && epoch < this->market_epochs.close;
}

#endif

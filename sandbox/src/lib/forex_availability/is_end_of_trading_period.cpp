#ifndef FOREX_AVAILABILITY_is_end_of_trading_period
#define FOREX_AVAILABILITY_is_end_of_trading_period

#include "forex_availability.h" // ForexAvailability

bool ForexAvailability::is_end_of_trading_period(const double epoch) {
  return epoch >= this->market_epochs.close - 60;
}

#endif

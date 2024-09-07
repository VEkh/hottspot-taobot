#ifndef NYSE_AVAILABILITY_is_market_open
#define NYSE_AVAILABILITY_is_market_open

#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "is_market_day.cpp"            // is_market_day
#include "nyse_availability.h"          // NyseAvailability

bool NyseAvailability::is_market_open(const double epoch) {
  if (!is_market_day(epoch)) {
    return false;
  }

  if (is_end_of_trading_period(epoch)) {
    return false;
  }

  return epoch >= this->market_open_epoch && epoch < this->market_close_epoch;
}

#endif

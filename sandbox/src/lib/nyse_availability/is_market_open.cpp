#ifndef NYSE_AVAILABILITY_is_market_open
#define NYSE_AVAILABILITY_is_market_open

#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "is_market_day.cpp"            // is_market_day
#include "nyse_availability.h"          // NyseAvailability

bool NyseAvailability::is_market_open(const double epoch,
                                      const bool include_pre = false) {
  if (!is_market_day(epoch)) {
    return false;
  }

  if (is_end_of_trading_period(epoch)) {
    return false;
  }

  const double open_epoch =
      include_pre ? this->market_epochs.pre : this->market_epochs.open;

  return epoch >= open_epoch && epoch < this->market_epochs.close;
}

#endif

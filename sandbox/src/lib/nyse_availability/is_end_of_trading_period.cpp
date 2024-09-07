#ifndef NYSE_AVAILABILITY_is_end_of_trading_period
#define NYSE_AVAILABILITY_is_end_of_trading_period

#include "nyse_availability.h" // NyseAvailability

bool NyseAvailability::is_end_of_trading_period(const double epoch) {
  return epoch >= this->market_close_epoch - 60;
}

#endif

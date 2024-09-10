#ifndef NYSE_AVAILABILITY_next_market_open_epoch
#define NYSE_AVAILABILITY_next_market_open_epoch

#include "get_market_open_epoch.cpp" // get_market_open_epoch
#include "nyse_availability.h"       // NyseAvailability

double NyseAvailability::next_market_open_epoch(const double epoch) {
  const int one_day_seconds = 24 * 60 * 60;

  return get_market_open_epoch(epoch + one_day_seconds);
}

#endif

#ifndef FOREX_AVAILABILITY_next_market_open_epoch
#define FOREX_AVAILABILITY_next_market_open_epoch

#include "forex_availability.h"      // ForexAvailability
#include "get_market_open_epoch.cpp" // get_market_open_epoch

double ForexAvailability::next_market_open_epoch(const double epoch) {
  const int one_day_seconds = 24 * 60 * 60;
  const double today_market_open_epoch = get_market_open_epoch(epoch);

  return epoch < today_market_open_epoch
             ? today_market_open_epoch
             : get_market_open_epoch(epoch + one_day_seconds);
}

#endif

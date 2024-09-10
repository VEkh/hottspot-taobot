#ifndef FOREX_AVAILABILITY_set_market_open_epoch
#define FOREX_AVAILABILITY_set_market_open_epoch

#include "forex_availability.h"      // ForexAvailability
#include "get_market_open_epoch.cpp" // get_market_open_epoch

void ForexAvailability::set_market_open_epoch(const double epoch) {
  const int one_day_seconds = 24 * 60 * 60;

  const double today_market_open_epoch = get_market_open_epoch(epoch);
  const double yesterday_market_open_epoch =
      get_market_open_epoch(epoch - one_day_seconds);

  this->market_epochs.open = epoch < today_market_open_epoch
                                 ? yesterday_market_open_epoch
                                 : today_market_open_epoch;
}

#endif

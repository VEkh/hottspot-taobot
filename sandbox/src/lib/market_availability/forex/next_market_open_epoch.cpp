#ifndef MARKET_AVAILABILITY__FOREX_next_market_open_epoch
#define MARKET_AVAILABILITY__FOREX_next_market_open_epoch

#include "forex.h"                   // MarketAvailability::Forex
#include "get_market_open_epoch.cpp" // get_market_open_epoch
#include "lib/utils/time.cpp"        // ::utils::time_

double MarketAvailability::Forex::next_market_open_epoch(const double epoch) {
  const int day_of_week = ::utils::time_::day_of_week(epoch);

  const double today_market_open_epoch = get_market_open_epoch(epoch);

  const double tomorrow_market_open_epoch =
      get_market_open_epoch(epoch + this->ONE_DAY_SECONDS);

  if (day_of_week == 6) {
    return tomorrow_market_open_epoch;
  }

  return epoch <= today_market_open_epoch ? today_market_open_epoch
                                          : tomorrow_market_open_epoch;
}

#endif

#ifndef MARKET_AVAILABILITY__FOREX_next_market_open_epoch
#define MARKET_AVAILABILITY__FOREX_next_market_open_epoch

#include "forex.h"                     // MarketAvailability::Forex
#include "get_market_open_epoch.cpp"   // get_market_open_epoch
#include "lib/utils/time.cpp"          // ::utils::time_
#include "week_market_bound_epoch.cpp" // week_market_bound_epoch

double MarketAvailability::Forex::next_market_open_epoch(const double epoch) {
  const int day_of_week = ::utils::time_::day_of_week(epoch);

  const double today_market_open_epoch = get_market_open_epoch(epoch);

  const double tomorrow_market_open_epoch =
      get_market_open_epoch(epoch + this->ONE_DAY_SECONDS);

  if (day_of_week == 6) {
    return week_market_bound_epoch(epoch + this->ONE_DAY_SECONDS, 0);
  }

  return epoch <= today_market_open_epoch ? today_market_open_epoch
                                          : tomorrow_market_open_epoch;
}

// TODO: Decide
double MarketAvailability::Forex::next_market_open_epoch(
    const double epoch, const int market_duration_hours) {
  if (!market_duration_hours) {
    return next_market_open_epoch(epoch);
  }

  const int day_of_week = ::utils::time_::day_of_week(epoch);

  if (day_of_week == 5 && epoch == week_market_bound_epoch(epoch, 5)) {
    return week_market_bound_epoch(epoch + 2 * this->ONE_DAY_SECONDS, 0);
  }

  if (day_of_week == 6) {
    return week_market_bound_epoch(epoch + this->ONE_DAY_SECONDS, 0);
  }

  return epoch;
}

#endif

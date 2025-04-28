#ifndef MARKET_AVAILABILITY__FOREX_get_close_epoch
#define MARKET_AVAILABILITY__FOREX_get_close_epoch

#include "epoch_at_time.cpp"           // epoch_at_time
#include "forex.h"                     // MarketAvailability::Forex
#include "week_market_bound_epoch.cpp" // week_market_bound_epoch
#include <algorithm>                   // std::min

double
MarketAvailability::Forex::get_close_epoch(const get_close_epoch_args_t args) {
  const double market_duration_hours = args.market_duration_hours;
  const std::string open_central_time = args.open_central_time;
  const double open_epoch = args.open_epoch;
  const bool should_upper_bound = args.should_upper_bound;

  const double end_of_week_epoch = week_market_bound_epoch(
      open_epoch, market_weekdays_t::MARKET_WEEKDAY_END);

  const double open_epoch_ = epoch_at_time(open_epoch, open_central_time);

  const double close_epoch =
      open_epoch_ + market_duration_hours * this->ONE_HOUR_SECONDS;

  if (!should_upper_bound) {
    return close_epoch;
  }

  return std::min(close_epoch, end_of_week_epoch);
}

#endif

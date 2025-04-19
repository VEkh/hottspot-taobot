#ifndef MARKET_AVAILABILITY__FOREX_week_market_bound_epoch
#define MARKET_AVAILABILITY__FOREX_week_market_bound_epoch

#include "forex.h"            // MarketAvailability::Forex
#include "lib/utils/time.cpp" // ::utils::time_
#include <string>             // std::string

double MarketAvailability::Forex::week_market_bound_epoch(
    const double epoch, const int bound_day_of_week) {
  const int day_of_week = ::utils::time_::day_of_week(epoch);

  const int bound_day_delta = bound_day_of_week - day_of_week;

  const double week_bound_epoch =
      epoch + (bound_day_delta * this->ONE_DAY_SECONDS);

  const std::string week_bound_iso_date =
      ::utils::time_::date_string(week_bound_epoch, "%F", "America/Chicago");

  return this->db_utils.timestamp_to_epoch(week_bound_iso_date + " 16:00:00",
                                           "America/Chicago");
}

#endif

#ifndef MARKET_AVAILABILITY__FOREX_set_market_open_epoch
#define MARKET_AVAILABILITY__FOREX_set_market_open_epoch

#include "forex.h"                   // MarketAvailability::Forex
#include "get_market_open_epoch.cpp" // get_market_open_epoch
#include "lib/utils/time.cpp"        // ::utils::time_

void MarketAvailability::Forex::set_market_open_epoch(const double epoch) {
  const double day_of_week = ::utils::time_::day_of_week(epoch);

  const int open_day_delta_days = 0 - day_of_week;
  const int open_day_delta_seconds =
      this->ONE_DAY_SECONDS * open_day_delta_days;

  const std::string open_iso_date = ::utils::time_::date_string(
      epoch + open_day_delta_seconds, "%F", "America/Chicago");

  const double open_epoch = this->db_utils.timestamp_to_epoch(
      open_iso_date + " 16:00:00", "America/Chicago");

  this->market_epochs.open = open_epoch;
}

#endif

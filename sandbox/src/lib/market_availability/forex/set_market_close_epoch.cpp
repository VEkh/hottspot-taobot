#ifndef MARKET_AVAILABILITY__FOREX_set_market_close_epoch
#define MARKET_AVAILABILITY__FOREX_set_market_close_epoch

#include "forex.h"            // MarketAvailability::Forex
#include "lib/utils/time.cpp" // ::utils::time_
#include <string>             // std::string

void MarketAvailability::Forex::set_market_close_epoch(const double epoch) {
  const double day_of_week = ::utils::time_::day_of_week(epoch);

  const int close_day_delta_days = 5 - day_of_week;
  const int close_day_delta_seconds =
      this->ONE_DAY_SECONDS * close_day_delta_days;

  const std::string close_iso_date = ::utils::time_::date_string(
      epoch + close_day_delta_seconds, "%F", "America/Chicago");

  const double close_epoch = this->db_utils.timestamp_to_epoch(
      close_iso_date + " 16:00:00", "America/Chicago");

  this->market_epochs.close = close_epoch;
}

#endif

#ifndef MARKET_AVAILABILITY__FOREX_set_market_close_epoch
#define MARKET_AVAILABILITY__FOREX_set_market_close_epoch

#include "forex.h"                   // MarketAvailability::Forex
#include "get_market_open_epoch.cpp" // get_market_open_epoch
#include "lib/utils/time.cpp"        // ::utils::time_
#include <string>                    // std::string

void MarketAvailability::Forex::set_market_close_epoch(const double epoch) {
  const double day_of_week = ::utils::time_::day_of_week(epoch);

  double close_epoch;

  if (day_of_week == 5) {
    const std::string close_iso_date =
        ::utils::time_::date_string(epoch, "%F", "America/Chicago");

    close_epoch = this->db_utils.timestamp_to_epoch(
        close_iso_date + " 16:00:00", "America/Chicago");
  } else if (day_of_week == 6) {
    close_epoch = epoch;
  } else {
    const double today_market_open_epoch = get_market_open_epoch(epoch);
    const int one_day_seconds = 24 * 60 * 60;

    const int offset = epoch >= today_market_open_epoch ? one_day_seconds : 0;

    const std::string close_iso_date =
        ::utils::time_::date_string(epoch + offset, "%F", "America/Chicago");

    close_epoch = this->db_utils.timestamp_to_epoch(
        close_iso_date + " 07:30:00", "America/Chicago");
  }

  this->market_epochs.close = close_epoch;
}

#endif

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

    const int offset =
        epoch >= today_market_open_epoch ? this->ONE_DAY_SECONDS : 0;

    const std::string close_iso_date =
        ::utils::time_::date_string(epoch + offset, "%F", "America/Chicago");

    close_epoch = this->db_utils.timestamp_to_epoch(
        close_iso_date + " 07:30:00", "America/Chicago");
  }

  this->market_epochs.close = close_epoch;
}

// TODO: Decide
#include "seconds_since_first_open_of_week.cpp" // seconds_since_first_open_of_week
#include "week_market_bound_epoch.cpp"          // week_market_bound_epoch

void MarketAvailability::Forex::set_market_close_epoch(
    const double epoch, const int market_duration_hours) {
  const double day_of_week = ::utils::time_::day_of_week(epoch);

  if (day_of_week == 6) {
    this->market_epochs.close = epoch;
    return;
  }

  const double close_epoch =
      week_market_bound_epoch(epoch, 0) +
      seconds_since_first_open_of_week(epoch, market_duration_hours, 1);

  const double last_close_of_week = week_market_bound_epoch(epoch, 5);

  this->market_epochs.close = std::min(close_epoch, last_close_of_week);

  printf("💦 market close: %s\n",
         ::utils::time_::date_string(this->market_epochs.close, "%F %T",
                                     "America/Chicago")
             .c_str());
}

#endif

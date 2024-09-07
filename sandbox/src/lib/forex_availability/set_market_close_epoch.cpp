#ifndef FOREX_AVAILABILITY_set_market_close_epoch
#define FOREX_AVAILABILITY_set_market_close_epoch

#include "forex_availability.h" // ForexAvailability
#include "lib/utils/time.cpp"   // ::utils::time_
#include <string>               // std::string

void ForexAvailability::set_market_close_epoch(const double epoch) {
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
    const int one_day_seconds = 24 * 60 * 60;

    const std::string close_iso_date = ::utils::time_::date_string(
        epoch + one_day_seconds, "%F", "America/Chicago");

    close_epoch = this->db_utils.timestamp_to_epoch(
        close_iso_date + " 07:30:00", "America/Chicago");
  }

  this->market_close_epoch = close_epoch;
}

#endif

#ifndef FOREX_AVAILABILITY_get_market_open_epoch
#define FOREX_AVAILABILITY_get_market_open_epoch

#include "forex_availability.h" // ForexAvailability
#include "lib/utils/time.cpp"   // ::utils::time_
#include <string>               // std::string

double ForexAvailability::get_market_open_epoch(const double epoch) {
  const std::string open_iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  const std::string open_time =
      ::utils::time_::day_of_week() == 0 ? " 16:00:00" : " 07:30:00";

  return this->db_utils.timestamp_to_epoch(open_iso_date + open_time,
                                           "America/Chicago");
}

#endif

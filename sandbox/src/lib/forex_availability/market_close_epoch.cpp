#ifndef FOREX_AVAILABILITY_market_close_epoch
#define FOREX_AVAILABILITY_market_close_epoch

#include "forex_availability.h" // ForexAvailability
#include "lib/utils/time.cpp"   // ::utils::time_
#include <string>               // std::string

double ForexAvailability::market_close_epoch(const double epoch) {
  const std::string iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  return this->db_utils.timestamp_to_epoch(iso_date + " 16:00:00",
                                           "America/Chicago");
}

#endif

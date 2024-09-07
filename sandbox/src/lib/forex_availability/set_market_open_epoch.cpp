#ifndef FOREX_AVAILABILITY_set_market_open_epoch
#define FOREX_AVAILABILITY_set_market_open_epoch

#include "forex_availability.h" // ForexAvailability
#include "lib/utils/time.cpp"   // ::utils::time_
#include <string>               // std::string

void ForexAvailability::set_market_open_epoch(const double epoch) {
  const std::string iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  this->market_open_epoch = this->db_utils.timestamp_to_epoch(
      iso_date + " 07:30:00", "America/Chicago");
}

#endif

#ifndef NYSE_AVAILABILITY_market_open_epoch
#define NYSE_AVAILABILITY_market_open_epoch

#include "lib/utils/time.cpp"  // ::utils::time_
#include "nyse_availability.h" // NyseAvailability
#include <string>              // std::string

double NyseAvailability::market_open_epoch(const double epoch) {
  const std::string iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  return this->db_utils.timestamp_to_epoch(iso_date + " 08:30:00",
                                           "America/Chicago");
}

#endif

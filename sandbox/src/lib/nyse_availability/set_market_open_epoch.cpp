#ifndef NYSE_AVAILABILITY_set_market_open_epoch
#define NYSE_AVAILABILITY_set_market_open_epoch

#include "lib/utils/time.cpp"  // ::utils::time_
#include "nyse_availability.h" // NyseAvailability
#include <string>              // std::string

void NyseAvailability::set_market_open_epoch(const double epoch,
                                             const int offset = 0) {
  const std::string iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  this->market_open_epoch = this->db_utils.timestamp_to_epoch(
                                iso_date + " 08:30:00", "America/Chicago") +
                            offset;
}

#endif

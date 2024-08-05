#ifndef NYSE_AVAILABILITY_market_close_epoch
#define NYSE_AVAILABILITY_market_close_epoch

#include "is_early_close_day.cpp" // is_early_close_day
#include "lib/utils/time.cpp"     // ::utils::time_
#include "nyse_availability.h"    // NyseAvailability
#include <string>                 // std::string

double NyseAvailability::market_close_epoch(const double epoch) {
  const std::string iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  const std::string close_time =
      is_early_close_day(epoch) ? " 12:00:00" : " 15:00:00";

  return this->db_utils.timestamp_to_epoch(iso_date + close_time,
                                           "America/Chicago");
}

#endif

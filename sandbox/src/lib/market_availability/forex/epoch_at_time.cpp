#ifndef MARKET_AVAILABILITY__FOREX_epoch_at_time
#define MARKET_AVAILABILITY__FOREX_epoch_at_time

#include "forex.h"            // MarketAvailability::Forex
#include "lib/utils/time.cpp" // ::utils::time_
#include <string>             // std::string

double
MarketAvailability::Forex::epoch_at_time(const double epoch,
                                         const std::string open_central_time) {
  const std::string open_iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  return this->db_utils.timestamp_to_epoch(
      open_iso_date + " " + open_central_time, "America/Chicago");
}

#endif

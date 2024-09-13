#ifndef MARKET_AVAILABILITY__NYSE_get_market_open_epoch
#define MARKET_AVAILABILITY__NYSE_get_market_open_epoch

#include "lib/utils/time.cpp" // ::utils::time_
#include "nyse.h"             // MarketAvailability::Nyse
#include <string>             // std::string

double MarketAvailability::Nyse::get_market_open_epoch(const double epoch,
                                                       const int offset = 0) {
  const std::string iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  return this->db_utils.timestamp_to_epoch(iso_date + " 08:30:00",
                                           "America/Chicago") +
         offset;
}

#endif

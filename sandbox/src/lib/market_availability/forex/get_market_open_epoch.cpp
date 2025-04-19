#ifndef MARKET_AVAILABILITY__FOREX_get_market_open_epoch
#define MARKET_AVAILABILITY__FOREX_get_market_open_epoch

#include "forex.h"            // MarketAvailability::Forex
#include "lib/utils/time.cpp" // ::utils::time_
#include <string>             // std::string

double MarketAvailability::Forex::get_market_open_epoch(
    const double epoch, const std::string standard_open_time) {
  const std::string open_iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  const std::string open_time =
      ::utils::time_::day_of_week(epoch) == 0 ? "16:00:00" : standard_open_time;

  return this->db_utils.timestamp_to_epoch(open_iso_date + " " + open_time,
                                           "America/Chicago");
}

// TODO: Decide
#include <time.h> // tm
double MarketAvailability::Forex::get_market_open_epoch(
    const double epoch, const int market_duration_hours,
    const std::string standard_open_time) {
  const tm current_tm = ::utils::time_::epoch_to_tm(epoch, "America/Chicago");

  const int market_session_n = current_tm.tm_hour / market_duration_hours;
  const int market_open_hour = market_session_n * market_duration_hours;

  tm market_open_tm = current_tm;

  market_open_tm.tm_hour = 0;
  market_open_tm.tm_min = 0;

  const std::string open_iso_date =
      ::utils::time_::date_string(epoch, "%F", "America/Chicago");

  const std::string open_time =
      ::utils::time_::day_of_week(epoch) == 0 ? "16:00:00" : standard_open_time;

  return this->db_utils.timestamp_to_epoch(open_iso_date + " " + open_time,
                                           "America/Chicago");
}

#endif

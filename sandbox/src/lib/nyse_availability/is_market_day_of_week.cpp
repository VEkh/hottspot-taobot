#ifndef NYSE_AVAILABILITY_is_market_day_of_week
#define NYSE_AVAILABILITY_is_market_day_of_week

#include "lib/utils/time.cpp"  // ::utils::time_
#include "nyse_availability.h" // NyseAvailability

bool NyseAvailability::is_market_day_of_week(const double epoch) {
  const int day_of_week_ = ::utils::time_::day_of_week(epoch);

  return day_of_week_ >= 1 && day_of_week_ <= 5;
}

#endif

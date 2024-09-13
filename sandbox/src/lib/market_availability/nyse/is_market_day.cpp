#ifndef MARKET_AVAILABILITY__NYSE_is_market_day
#define MARKET_AVAILABILITY__NYSE_is_market_day

#include "is_market_day_of_week.cpp" // is_market_day_of_week
#include "nyse.h" // MarketAvailability::Nyse, is_holiday, is_in_date_lookup

bool MarketAvailability::Nyse::is_market_day(const double epoch) {
  if (!is_market_day_of_week(epoch)) {
    return false;
  }

  if (is_in_date_lookup(this->bad_data, epoch)) {
    return false;
  }

  if (is_holiday(epoch)) {
    return false;
  }

  return true;
}

#endif

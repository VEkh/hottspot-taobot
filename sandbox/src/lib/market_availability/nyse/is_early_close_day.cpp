#ifndef MARKET_AVAILABILITY__NYSE_is_early_close_day
#define MARKET_AVAILABILITY__NYSE_is_early_close_day

#include "nyse.h" // MarketAvailability::Nyse, is_in_date_lookup

bool MarketAvailability::Nyse::is_early_close_day(const double epoch) {
  return is_in_date_lookup(this->early_closes, epoch);
}

#endif

#ifndef DB__FIVE_MIN_CANDLE_quote_to_bounds
#define DB__FIVE_MIN_CANDLE_quote_to_bounds

#include "five_min_candle.h" // DB::FiveMinCandle, quote_t
#include <time.h>            // localtime, mktime, time, tm

DB::FiveMinCandle::candle_bounds_t
DB::FiveMinCandle::quote_to_bounds(const quote_t &quote) {
  const int n = this->CANDLE_DURATION_MINUTES;
  const long int timestamp = quote.timestamp;

  tm closed_at = *localtime(&timestamp);
  tm opened_at = *localtime(&timestamp);

  closed_at.tm_min = ((closed_at.tm_min + n) / n) * n;
  closed_at.tm_sec = 0;

  opened_at.tm_min = (opened_at.tm_min / n) * n;
  opened_at.tm_sec = 0;

  return {
      .closed_at = (double)mktime(&closed_at),
      .opened_at = (double)mktime(&opened_at),
  };
}

#endif

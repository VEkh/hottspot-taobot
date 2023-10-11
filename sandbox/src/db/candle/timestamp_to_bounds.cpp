#ifndef DB__CANDLE_timestamp_to_bounds
#define DB__CANDLE_timestamp_to_bounds

#include "candle.h" // DB::Candle
#include <time.h>   // localtime, mktime, time, tm

DB::Candle::candle_bounds_t
DB::Candle::timestamp_to_bounds(const int n, const long int timestamp) {
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

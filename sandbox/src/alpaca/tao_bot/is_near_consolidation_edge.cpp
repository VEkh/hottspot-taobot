// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_near_consolidation_edge
#define ALPACA__TAO_BOT_is_near_consolidation_edge

#include "candles_range.cpp" // candles_range
#include "current_mid.cpp"   // current_mid
#include "tao_bot.h"         // Alpaca::TaoBot, range_t
#include <math.h>            // abs

bool Alpaca::TaoBot::is_near_consolidation_edge(const int range_n) {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double mid = current_mid();

  range_t range = candles_range(range_n);

  const double high_delta = range.high - mid;
  const double low_delta = mid - range.low;

  if (high_delta > 0 && high_delta <= 10 * static_one_sec_variance) {
    return true;
  }

  if (low_delta > 0 && low_delta <= 10 * static_one_sec_variance) {
    return true;
  }

  return false;
}

#endif

// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_breaking_consolidation
#define ALPACA__TAO_BOT_is_breaking_consolidation

#include "candles_range.cpp"    // candles_range
#include "current_mid.cpp"      // current_mid
#include "is_consolidating.cpp" // is_consolidating
#include "tao_bot.h"            // Alpaca::TaoBot, range_t
#include <math.h>               // abs

bool Alpaca::TaoBot::is_breaking_consolidation(const int range_n) {
  const double mid = current_mid();

  if (!is_consolidating(range_n)) {
    return false;
  }

  range_t range = candles_range(range_n);

  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double buffer = 0 * static_one_sec_variance;

  return mid >= range.high + buffer || mid < range.low - buffer;
}

#endif

// TODO: Define
#ifndef ALPACA__TAO_BOT_is_closer_to_consolidation_low
#define ALPACA__TAO_BOT_is_closer_to_consolidation_low

#include "candles_range.cpp" // candles_range
#include "current_mid.cpp"   // current_mid
#include "tao_bot.h"         // Alpaca::TaoBot, range_t

bool Alpaca::TaoBot::is_closer_to_consolidation_low(const int range_n) {
  const int half_candles_n = range_n / 2;
  const range_t range = candles_range(range_n);

  const double mid = current_mid();
  const double high_delta = range.high - mid;
  const double low_delta = mid - range.low;

  return low_delta <= high_delta;
}

#endif

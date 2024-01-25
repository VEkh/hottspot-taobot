// TODO: Decide
#ifndef ALPACA__TAO_BOT_relation_to_consolidation
#define ALPACA__TAO_BOT_relation_to_consolidation

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Alpaca::TaoBot, range_t

Alpaca::TaoBot::trend_t
Alpaca::TaoBot::relation_to_consolidation(const range_t range) {
  const double mid = current_mid();

  if (mid > range.high) {
    return trend_t::TREND_UP;
  }

  if (mid < range.low) {
    return trend_t::TREND_DOWN;
  }

  return trend_t::TREND_CONSOLIDATION;
}

#endif

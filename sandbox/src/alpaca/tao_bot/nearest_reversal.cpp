// TODO: Decide
#ifndef ALPACA__TAO_BOT_nearest_reversal
#define ALPACA__TAO_BOT_nearest_reversal

#include "tao_bot.h" // Alpaca::TaoBot

Alpaca::TaoBot::reversal_t
Alpaca::TaoBot::nearest_reversal(reversals_t &reversals_) {
  const double recent_high_at =
      reversals_.highs.empty() ? 0 : reversals_.highs.rbegin()->first;

  const double recent_low_at =
      reversals_.lows.empty() ? 0 : reversals_.lows.rbegin()->first;

  if (recent_high_at && recent_high_at > recent_low_at) {
    return reversals_.highs.rbegin()->second;
  }

  return reversals_.lows.rbegin()->second;
}

#endif

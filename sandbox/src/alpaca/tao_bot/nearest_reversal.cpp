// TODO: Decide
#ifndef ALPACA__TAO_BOT_nearest_reversal
#define ALPACA__TAO_BOT_nearest_reversal

#include "tao_bot.h" // Alpaca::TaoBot

Alpaca::TaoBot::reversal_t Alpaca::TaoBot::nearest_reversal() {
  const double recent_high_at =
      this->reversals.highs.empty() ? 0 : this->reversals.highs.rbegin()->first;

  const double recent_low_at =
      this->reversals.lows.empty() ? 0 : this->reversals.lows.rbegin()->first;

  if (recent_high_at && recent_high_at > recent_low_at) {
    return this->reversals.highs.rbegin()->second;
  }

  return this->reversals.lows.rbegin()->second;
}

#endif

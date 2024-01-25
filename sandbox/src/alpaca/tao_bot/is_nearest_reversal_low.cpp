#ifndef ALPACA__TAO_BOT_is_nearest_reversal_low
#define ALPACA__TAO_BOT_is_nearest_reversal_low

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::is_nearest_reversal_low() {
  if (this->reversals.highs.empty() && this->reversals.lows.empty()) {
    return true;
  }

  const double recent_high_at =
      this->reversals.highs.empty() ? 0 : this->reversals.highs.rbegin()->first;

  const double recent_low_at =
      this->reversals.lows.empty() ? 0 : this->reversals.lows.rbegin()->first;

  if (recent_high_at && recent_high_at > recent_low_at) {
    return false;
  }

  if (recent_low_at && recent_low_at > recent_high_at) {
    return true;
  }

  return true;
}

#endif

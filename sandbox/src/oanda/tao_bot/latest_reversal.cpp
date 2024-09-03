#ifndef OANDA__TAO_BOT_latest_reversal
#define OANDA__TAO_BOT_latest_reversal

#include "tao_bot.h" // Oanda::TaoBot, reversal_type_t

Oanda::TaoBot::reversal_t Oanda::TaoBot::latest_reversal(
    reversals_t &reversals_,
    const reversal_type_t type = reversal_type_t::REVERSAL_NULL) {
  const reversal_t recent_high = reversals_.highs.empty()
                                     ? reversal_t()
                                     : reversals_.highs.rbegin()->second;
  const reversal_t recent_low =
      reversals_.lows.empty() ? reversal_t() : reversals_.lows.rbegin()->second;

  if (type == reversal_type_t::REVERSAL_HIGH) {
    return recent_high;
  }

  if (type == reversal_type_t::REVERSAL_LOW) {
    return recent_low;
  }

  if (recent_high.at && recent_high.at > recent_low.at) {
    return recent_high;
  }

  return recent_low;
}

#endif

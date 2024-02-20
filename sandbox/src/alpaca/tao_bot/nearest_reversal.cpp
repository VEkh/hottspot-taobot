// TODO: Decide
#ifndef ALPACA__TAO_BOT_nearest_reversal
#define ALPACA__TAO_BOT_nearest_reversal

#include "tao_bot.h" // Alpaca::TaoBot
#include <string>    // std::string

Alpaca::TaoBot::reversal_t
Alpaca::TaoBot::nearest_reversal(reversals_t &reversals_,
                                 const std::string key = "") {
  const reversal_t recent_high = reversals_.highs.rbegin()->second;
  const reversal_t recent_low = reversals_.lows.rbegin()->second;

  if (key == "high") {
    return recent_high;
  }

  if (key == "low") {
    return recent_low;
  }

  if (recent_high.at && recent_high.at > recent_low.at) {
    return recent_high;
  }

  return recent_low;
}

#endif

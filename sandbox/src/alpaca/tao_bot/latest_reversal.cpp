// TODO: Decide
#ifndef ALPACA__TAO_BOT_latest_reversal
#define ALPACA__TAO_BOT_latest_reversal

#include "tao_bot.h" // Alpaca::TaoBot
#include <string>    // std::string

Alpaca::TaoBot::reversal_t
Alpaca::TaoBot::latest_reversal(reversals_t &reversals_,
                                const std::string key = "") {
  const reversal_t recent_high = reversals_.highs.empty()
                                     ? reversal_t()
                                     : reversals_.highs.rbegin()->second;
  const reversal_t recent_low =
      reversals_.lows.empty() ? reversal_t() : reversals_.lows.rbegin()->second;

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
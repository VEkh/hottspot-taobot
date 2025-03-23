#ifndef ALPACA__TAO_BOT_latest_reversal
#define ALPACA__TAO_BOT_latest_reversal

#include "tao_bot.h" // Alpaca::TaoBot, reversal_type_t

Alpaca::TaoBot::reversal_t Alpaca::TaoBot::latest_reversal(
    reversals_t &reversals_,
    const reversal_type_t reversal_type = reversal_type_t::REVERSAL_NULL,
    const bool only_records = false) { // TODO: Decide
  reversal_t recent_high;
  reversal_t recent_low;
  std::map<double, reversal_t>::reverse_iterator it;

  const int ref_epoch_minute = this->current_epoch / 60;

  if (reversal_type == reversal_type_t::REVERSAL_HIGH ||
      reversal_type == reversal_type_t::REVERSAL_NULL) {
    for (it = reversals_.highs.rbegin(); it != reversals_.highs.rend(); it++) {
      const int reversal_minute = it->first / 60;
      const int shifted_reversal_minute =
          reversal_minute + reversals_.timeframe_minutes * 0.5;

      if (shifted_reversal_minute < ref_epoch_minute) {
        // TODO: Decide
        if (only_records && !it->second.is_record) {
          continue;
        }

        recent_high = it->second;

        break;
      }
    }
  }

  if (reversal_type == reversal_type_t::REVERSAL_LOW ||
      reversal_type == reversal_type_t::REVERSAL_NULL) {
    for (it = reversals_.lows.rbegin(); it != reversals_.lows.rend(); it++) {
      const int reversal_minute = it->first / 60;
      const int shifted_reversal_minute =
          reversal_minute + reversals_.timeframe_minutes * 0.5;

      if (shifted_reversal_minute < ref_epoch_minute) {
        // TODO: Decide
        if (only_records && !it->second.is_record) {
          continue;
        }

        recent_low = it->second;

        break;
      }
    }
  }

  if (reversal_type == reversal_type_t::REVERSAL_HIGH) {
    return recent_high;
  }

  if (reversal_type == reversal_type_t::REVERSAL_LOW) {
    return recent_low;
  }

  if (recent_high.at && recent_high.at > recent_low.at) {
    return recent_high;
  }

  return recent_low;
}

#endif

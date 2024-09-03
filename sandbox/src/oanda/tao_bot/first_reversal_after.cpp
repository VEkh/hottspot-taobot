#ifndef OANDA__TAO_BOT_first_reversal_after
#define OANDA__TAO_BOT_first_reversal_after

#include "tao_bot.h" // Oanda::TaoBot,  reversal_t, reversals_t, reversal_type_t
#include <map>       // std::map

Oanda::TaoBot::reversal_t Oanda::TaoBot::first_reversal_after(
    reversals_t &reversals_, const double ref_timestamp,
    const reversal_type_t reversal_type = reversal_type_t::REVERSAL_NULL,
    const bool only_running_record = false) {
  if (!ref_timestamp) {
    return reversal_t();
  }

  if (!reversals_.timeframe_minutes) {
    return reversal_t();
  }

  const int ref_timestamp_minute = ref_timestamp / 60;

  reversal_t newer_high;
  reversal_t newer_low;
  std::map<double, reversal_t>::iterator it;

  if (reversal_type == reversal_type_t::REVERSAL_HIGH ||
      reversal_type == reversal_type_t::REVERSAL_NULL) {
    for (it = reversals_.highs.begin(); it != reversals_.highs.end(); it++) {
      const int reversal_minute = it->first / 60;

      if (only_running_record && !it->second.is_running_record) {
        continue;
      }

      if (reversal_minute >= ref_timestamp_minute) {
        newer_high = it->second;
        break;
      }
    }
  }

  if (reversal_type == reversal_type_t::REVERSAL_LOW ||
      reversal_type == reversal_type_t::REVERSAL_NULL) {
    for (it = reversals_.lows.begin(); it != reversals_.lows.end(); it++) {
      const int reversal_minute = it->first / 60;

      if (only_running_record && !it->second.is_running_record) {
        continue;
      }

      if (reversal_minute >= ref_timestamp_minute) {
        newer_low = it->second;
        break;
      }
    }
  }

  if (reversal_type == reversal_type_t::REVERSAL_HIGH) {
    return newer_high;
  }

  if (reversal_type == reversal_type_t::REVERSAL_LOW) {
    return newer_low;
  }

  if (newer_high.at && newer_low.at) {
    return newer_high.at < newer_low.at ? newer_high : newer_low;
  }

  return newer_high.at ? newer_high : newer_low;
}

#endif

#ifndef ALPACA__TAO_BOT_latest_record_reversal
#define ALPACA__TAO_BOT_latest_record_reversal

#include "tao_bot.h" // Alpaca::TaoBot, reversal_t, reversal_type_t
#include <map>       // std::map
#include <string>    // std::string

Alpaca::TaoBot::reversal_t Alpaca::TaoBot::latest_record_reversal(
    reversals_t &reversals_,
    const reversal_type_t type = reversal_type_t::REVERSAL_NULL) {
  std::map<double, reversal_t>::reverse_iterator it;
  reversal_t record_high;
  reversal_t record_low;

  for (it = reversals_.highs.rbegin(); it != reversals_.highs.rend(); it++) {
    if (it->second.is_running_record) {
      record_high = it->second;
    }
  }

  for (it = reversals_.lows.rbegin(); it != reversals_.lows.rend(); it++) {
    if (it->second.is_running_record) {
      record_low = it->second;
    }
  }

  if (type == reversal_type_t::REVERSAL_HIGH) {
    return record_high;
  }

  if (type == reversal_type_t::REVERSAL_LOW) {
    return record_low;
  }

  if (record_high.at > record_low.at) {
    return record_high;
  }

  return record_low;
}

#endif

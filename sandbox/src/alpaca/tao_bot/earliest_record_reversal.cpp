// TODO: Decide
#ifndef ALPACA__TAO_BOT_earliest_record_reversal
#define ALPACA__TAO_BOT_earliest_record_reversal

#include "tao_bot.h" // Alpaca::TaoBot, reversal_t
#include <map>       // std::map
#include <string>    // std::string

Alpaca::TaoBot::reversal_t
Alpaca::TaoBot::earliest_record_reversal(reversals_t &reversals_) {
  std::map<double, reversal_t>::iterator it;
  reversal_t record_high;
  reversal_t record_low;

  for (it = reversals_.highs.begin(); it != reversals_.highs.end(); it++) {
    if (it->second.is_record) {
      record_high = it->second;
    }
  }

  for (it = reversals_.lows.begin(); it != reversals_.lows.end(); it++) {
    if (it->second.is_record) {
      record_low = it->second;
    }
  }

  if (record_high.at < record_low.at) {
    return record_high;
  }

  return record_low;
}

#endif

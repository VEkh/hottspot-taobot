// TODO: Decide
#ifndef ALPACA__TAO_BOT_nearest_record_reversal
#define ALPACA__TAO_BOT_nearest_record_reversal

#include "tao_bot.h" // Alpaca::TaoBot, reversal_t
#include <map>       // std::map

Alpaca::TaoBot::reversal_t Alpaca::TaoBot::nearest_record_reversal() {
  std::map<double, reversal_t>::reverse_iterator it;
  reversal_t record_high;
  reversal_t record_low;

  for (it = this->reversals.highs.rbegin(); it != this->reversals.highs.rend();
       it++) {
    if (it->second.is_record) {
      record_high = it->second;
    }
  }

  for (it = this->reversals.lows.rbegin(); it != this->reversals.lows.rend();
       it++) {
    if (it->second.is_record) {
      record_low = it->second;
    }
  }

  if (record_high.at > record_low.at) {
    return record_high;
  }

  return record_low;
}

#endif

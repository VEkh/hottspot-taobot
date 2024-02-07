// TODO: Decide
#ifndef ALPACA__TAO_BOT_nearest_record_reversal
#define ALPACA__TAO_BOT_nearest_record_reversal

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, reversal_t
#include <map>       // std::map
#include <utility>   // std::pair

std::pair<double, Alpaca::TaoBot::reversal_t>
Alpaca::TaoBot::nearest_record_reversal(const double epoch) {
  std::map<double, reversal_t>::reverse_iterator it;
  std::pair<double, reversal_t> record_high;
  std::pair<double, reversal_t> record_low;

  for (it = this->reversals.highs.rbegin(); it != this->reversals.highs.rend();
       it++) {
    if (it->first <= epoch && it->second.is_record) {
      record_high = *it;
    }
  }

  for (it = this->reversals.lows.rbegin(); it != this->reversals.lows.rend();
       it++) {
    if (it->first <= epoch && it->second.is_record) {
      record_low = *it;
    }
  }

  if (record_high.first > record_low.first) {
    return record_high;
  }

  return record_low;
}

#endif

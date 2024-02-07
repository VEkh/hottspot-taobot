// TODO: Decide
#ifndef ALPACA__TAO_BOT_nearest_opening_reversal
#define ALPACA__TAO_BOT_nearest_opening_reversal

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, reversal_t
#include <map>       // std::map
#include <utility>   // std::pair

std::pair<double, Alpaca::TaoBot::reversal_t>
Alpaca::TaoBot::nearest_opening_reversal(const order_action_t action,
                                         const double epoch) {
  std::map<double, reversal_t> reversals_ = action == order_action_t::BUY
                                                ? this->reversals.lows
                                                : this->reversals.highs;

  std::map<double, reversal_t>::reverse_iterator it;

  for (it = reversals_.rbegin(); it != reversals_.rend(); it++) {
    if (it->first <= epoch) {
      return *it;
    }
  }

  return {0, reversal_t()};
}

#endif

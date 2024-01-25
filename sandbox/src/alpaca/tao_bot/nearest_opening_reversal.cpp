// TODO: Decide
#ifndef ALPACA__TAO_BOT_nearest_opening_reversal
#define ALPACA__TAO_BOT_nearest_opening_reversal

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, reversal_t
#include <map>       // std::map
#include <utility>   // std::pair

std::pair<double, double>
Alpaca::TaoBot::nearest_opening_reversal(const order_t *order) {
  const double epoch = order->timestamp;

  std::map<double, double> reversals_ = order->action == order_action_t::BUY
                                            ? this->reversals.lows
                                            : this->reversals.highs;

  std::map<double, double>::reverse_iterator it;

  for (it = reversals_.rbegin(); it != reversals_.rend(); it++) {
    if (it->first <= epoch) {
      return *it;
    }
  }

  return {0, 0};
}

#endif

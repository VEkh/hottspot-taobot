// TODO: Decide
#ifndef ALPACA__TAO_BOT_nearest_opening_reversal
#define ALPACA__TAO_BOT_nearest_opening_reversal

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, reversal_t
#include <list>      // std::list

Alpaca::TaoBot::reversal_t
Alpaca::TaoBot::nearest_opening_reversal(const order_t *order) {
  const double epoch = order->timestamp;

  std::list<reversal_t> reversals_ = order->action == order_action_t::BUY
                                         ? this->reversals.lows
                                         : this->reversals.highs;

  std::list<reversal_t>::reverse_iterator it;

  for (it = reversals_.rbegin(); it != reversals_.rend(); it++) {
    if (it->at <= epoch) {
      return *it;
    }
  }

  return reversal_t();
}

#endif

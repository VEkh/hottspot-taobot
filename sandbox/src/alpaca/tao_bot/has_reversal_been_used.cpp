#ifndef ALPACA__TAO_BOT_has_reversal_been_used
#define ALPACA__TAO_BOT_has_reversal_been_used

#include "is_trending.cpp" // is_trending
#include "tao_bot.h"       // Alpaca::TaoBot, position_t, reversal_t
#include <vector>          // std::vector

bool Alpaca::TaoBot::has_reversal_been_used(const reversal_t reversal) {
  std::vector<position_t>::reverse_iterator it;

  if (is_trending()) {
    return false;
  }

  // TODO: Decide
  if (this->should_stop_profit ||
      !this->api_client.config.reverse_profit_during.empty()) {
    return false;
  }

  for (it = this->closed_positions.rbegin();
       it != this->closed_positions.rend(); it++) {
    if (it->open_order.entry_reversal.type == reversal.type &&
        it->open_order.entry_reversal.at == reversal.at) {
      return true;
    }
  }

  return false;
}

#endif

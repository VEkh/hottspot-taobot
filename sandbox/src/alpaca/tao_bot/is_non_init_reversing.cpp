// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_non_init_reversing
#define ALPACA__TAO_BOT_is_non_init_reversing

#include "is_trending.cpp" // is_trending
#include "tao_bot.h"       // Alpaca::TaoBot

bool Alpaca::TaoBot::is_non_init_reversing(const order_t *order) {
  if (!order) {
    return false;
  }

  if (this->closed_positions.empty()) {
    return false;
  }

  return !is_trending();
}

#endif

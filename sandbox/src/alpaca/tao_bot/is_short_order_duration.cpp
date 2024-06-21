// TODO: Decide
#ifndef ALPACA__CLIENT_is_short_order_duration
#define ALPACA__CLIENT_is_short_order_duration

#include "order_duration.cpp" // order_duration
#include "tao_bot.h"          // Alpaca::TaoBot, order_t

bool Alpaca::TaoBot::is_short_order_duration(const order_t *order) {
  const int limit = 30 * 60;

  return order_duration(order) < limit;
}

#endif

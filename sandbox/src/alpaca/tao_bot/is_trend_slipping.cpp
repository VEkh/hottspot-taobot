#ifndef ALPACA__TAO_BOT_is_trend_slipping
#define ALPACA__TAO_BOT_is_trend_slipping

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h"                // Alpaca::TaoBot, order_action_t

bool Alpaca::TaoBot::is_trend_slipping(const order_t *order) {
  return day_range_percentile(order, order->profit) < this->EQUATOR_PERCENTILE;
}

#endif

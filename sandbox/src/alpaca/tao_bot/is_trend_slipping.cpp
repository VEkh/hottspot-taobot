// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_trend_slipping
#define ALPACA__TAO_BOT_is_trend_slipping

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h"                // Alpaca::TaoBot, order_action_t

bool Alpaca::TaoBot::is_trend_slipping(const order_t *order) {
  const double trend_slip_percentile =
      this->api_client.config.trend_slip_percentile;

  if (!trend_slip_percentile) {
    return true;
  }

  return day_range_percentile(order, order->profit) < trend_slip_percentile;
}

#endif

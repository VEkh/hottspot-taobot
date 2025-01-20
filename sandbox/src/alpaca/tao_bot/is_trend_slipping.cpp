#ifndef ALPACA__TAO_BOT_is_trend_slipping
#define ALPACA__TAO_BOT_is_trend_slipping

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h"                // Alpaca::TaoBot, order_action_t

bool Alpaca::TaoBot::is_trend_slipping(const order_t *order) {
  // TODO: Decide
  const double threshold = this->api_client.config.should_stop_profit
                               ? this->TREND_SLIP_PERCENTILE
                               : this->EQUATOR_PERCENTILE;

  return is_trend_slipping(order, threshold);
}

// TODO: Decide
bool Alpaca::TaoBot::is_trend_slipping(const order_t *order,
                                       const double threshold) {
  return day_range_percentile(this->day_candle, order, order->profit) <
         threshold;
}

#endif

#ifndef OANDA__TAO_BOT_is_trend_slipping
#define OANDA__TAO_BOT_is_trend_slipping

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h"                // Oanda::TaoBot, order_action_t

bool Oanda::TaoBot::is_trend_slipping(const order_t *order) {
  return day_range_percentile(this->day_candle, order, order->profit) <
         this->TREND_SLIP_PERCENTILE;
}

#endif

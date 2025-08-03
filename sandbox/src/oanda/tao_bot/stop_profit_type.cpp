#ifndef OANDA__TAO_BOT_stop_profit_type
#define OANDA__TAO_BOT_stop_profit_type

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h"                // Oanda::TaoBot, stop_profit_type_t
#include <algorithm>                // std::min

Oanda::TaoBot::stop_profit_type_t
Oanda::TaoBot::stop_profit_type(candle_t candle, const double execution_price) {
  const double execution_price_percentile =
      day_range_percentile(candle, execution_price);

  const double normalized_execution_price_percentile =
      std::min(100.0 - execution_price_percentile, execution_price_percentile);

  if (normalized_execution_price_percentile <= 10.0) {
    return stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE;
  }

  return stop_profit_type_t::STOP_PROFIT_CROSS_RANGE;
}

Oanda::TaoBot::stop_profit_type_t
Oanda::TaoBot::stop_profit_type(const order_t *order) {
  return stop_profit_type(order->day_candle, order->execution_price);
}

#endif

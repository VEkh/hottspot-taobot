#ifndef ALPACA__TAO_BOT_max_profit_day_range_percent
#define ALPACA__TAO_BOT_max_profit_day_range_percent

#include "tao_bot.h" // Alpaca::TaoBot, order_t

double Alpaca::TaoBot::max_profit_day_range_percent(const order_t *order) {
  if (!order) {
    return 0.0;
  }

  return 100.0 * (order->max_profit / this->day_candle.range());
}

#endif

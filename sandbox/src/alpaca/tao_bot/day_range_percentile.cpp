// TODO: Decide
#ifndef ALPACA__TAO_BOT_day_range_percentile
#define ALPACA__TAO_BOT_day_range_percentile

#include "tao_bot.h" // Alpaca::TaoBot, order_t
#include <math.h>    // isnan

double Alpaca::TaoBot::day_range_percentile(const double mid) {
  const double percentile =
      100.0 * ((mid - this->day_candle.low) / this->day_candle.range());

  return isnan(percentile) ? 0.0 : percentile;
}

double Alpaca::TaoBot::day_range_percentile(const order_t *order,
                                            const double profit) {
  const double execution_mid = order->execution_price;
  const double profit_mid = order->action == order_action_t::BUY
                                ? execution_mid + profit
                                : execution_mid - profit;

  const double percentile = day_range_percentile(profit_mid);

  if (order->action == order_action_t::BUY) {
    return percentile;
  }

  return 100.0 - percentile;
}

#endif

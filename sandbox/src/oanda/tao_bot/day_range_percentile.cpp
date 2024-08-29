#ifndef OANDA__TAO_BOT_day_range_percentile
#define OANDA__TAO_BOT_day_range_percentile

#include "tao_bot.h" // Oanda::TaoBot, order_t
#include <math.h>    // isnan

double Oanda::TaoBot::day_range_percentile(const double mid) {
  const double percentile =
      100.0 * ((mid - this->day_candle.low) / this->day_candle.range());

  return isnan(percentile) ? 0.0 : percentile;
}

double Oanda::TaoBot::day_range_percentile(const order_t *order,
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

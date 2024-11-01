#ifndef OANDA__TAO_BOT_day_range_percentile
#define OANDA__TAO_BOT_day_range_percentile

#include "tao_bot.h" // Oanda::TaoBot, candle_t, order_t
#include <math.h>    // isnan

double Oanda::TaoBot::day_range_percentile(const double mid) {
  return day_range_percentile(mid, this->day_candle);
}

double Oanda::TaoBot::day_range_percentile(const double mid,
                                           const bool invert) {
  const double percentile = day_range_percentile(mid);

  return invert ? 100.0 - percentile : percentile;
}

double Oanda::TaoBot::day_range_percentile(const double mid, candle_t candle) {
  const double percentile = 100.0 * ((mid - candle.low) / candle.range());

  return isnan(percentile) ? 0.0 : percentile;
}

double Oanda::TaoBot::day_range_percentile(const order_t *order,
                                           const double profit) {
  const double execution_mid = order->execution_price;
  const double profit_mid = order->action == order_action_t::BUY
                                ? execution_mid + profit
                                : execution_mid - profit;

  return day_range_percentile(profit_mid,
                              order->action == order_action_t::SELL);
}

#endif

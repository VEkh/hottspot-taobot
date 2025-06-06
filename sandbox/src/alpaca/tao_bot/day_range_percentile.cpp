#ifndef ALPACA__TAO_BOT_day_range_percentile
#define ALPACA__TAO_BOT_day_range_percentile

#include "tao_bot.h" // Alpaca::TaoBot, candle_t, order_t
#include <math.h>    // isnan

double Alpaca::TaoBot::day_range_percentile(candle_t candle, const double mid,
                                            const bool invert = false) {
  const double percentile = 100.0 * ((mid - candle.low) / candle.range());
  const double real_percentile = isnan(percentile) ? 0.0 : percentile;

  return invert ? 100.0 - real_percentile : real_percentile;
}

double Alpaca::TaoBot::day_range_percentile(candle_t candle,
                                            const order_t *order,
                                            const double profit) {
  const double execution_price = order->execution_price;
  const double profit_mid = order->action == order_action_t::BUY
                                ? execution_price + profit
                                : execution_price - profit;

  return day_range_percentile(candle, profit_mid,
                              order->action == order_action_t::SELL);
}

#endif

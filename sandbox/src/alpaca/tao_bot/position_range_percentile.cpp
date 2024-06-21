// TODO: Decide
#ifndef ALPACA__TAO_BOT_position_range_percentile
#define ALPACA__TAO_BOT_position_range_percentile

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, order_t
#include <math.h>    // abs, isnan

double Alpaca::TaoBot::position_range_percentile(const order_t *order,
                                                 const double profit) {
  if (!order) {
    return 0.0;
  }

  const order_action_t action = order->action;

  const double entry_reversal_mid = order->entry_reversal.mid;
  const double execution_mid = order->execution_price;
  const double mid = action == order_action_t::BUY ? execution_mid + profit
                                                   : execution_mid - profit;

  const double low_delta = abs(mid - entry_reversal_mid);

  const double high = action == order_action_t::BUY
                          ? execution_mid + order->max_profit
                          : execution_mid - order->max_profit;

  const double range = abs(high - entry_reversal_mid);

  const double percentile = 100.0 * (low_delta / range);

  return isnan(percentile) ? 0.0 : percentile;
}

#endif

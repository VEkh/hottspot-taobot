#if !defined ETRADE__STOCK_BOT_compute_trailing_stop
#define ETRADE__STOCK_BOT_compute_trailing_stop

#include "compute_max_loss.cpp" // compute_max_loss
#include "stock_bot.h"          // ETrade::StockBot,  order_t
#include <math.h>               // exp

double ETrade::StockBot::compute_trailing_stop(const order_t *open_order,
                                               const double tick_velocity) {
  const double max_loss = compute_max_loss();

  if (open_order->profit < 0) {
    return max_loss;
  }

  const double x = open_order->profit;
  const double velocity_coefficient = 1 + (tick_velocity * 100);
  const double x_scale = 2.0 / velocity_coefficient;
  const double y_scale = 2 * max_loss;

  return y_scale * (1 / (1 + exp(x_scale * x)));
}

#endif

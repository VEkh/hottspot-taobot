#if !defined ETRADE__STRADDLE_set_trailing_stop_price
#define ETRADE__STRADDLE_set_trailing_stop_price

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include "straddle.h"        // ETrade::Straddle, order_t, quote, stream_format
#include <algorithm>         // std::max, std::min
#include <iostream>          // std::cout, std::endl
#include <math.h>            // INFINITY, exp, pow

const double TRAILING_STOP_LOSS_RATIO = 0.15;

double compute_trailing_stop(const double day_range, const order_t *open_order,
                             const double tick_velocity_10,
                             const double tick_velocity_30) {
  const double max_loss = TRAILING_STOP_LOSS_RATIO * day_range;

  if (open_order->profit < 0) {
    return max_loss;
  }

  const double x = open_order->profit;
  const double velocity_coefficient_10 = 1 + (tick_velocity_10 * 100);
  const double velocity_coefficient_30 = 1 + (tick_velocity_30 * 100);
  const double x_scale =
      2.0 / (velocity_coefficient_10 * 2 * velocity_coefficient_30);
  const double y_scale = 2 * max_loss;

  return y_scale * (1 / (1 + exp(x_scale * x)));
}

void ETrade::Straddle::set_trailing_stop_price(order_t *close_order,
                                               const order_t *open_order) {
  const double execution_price = open_order->execution_price;

  if (!execution_price) {
    return;
  }

  json current_quote = quotes.back();
  json reference_quote = quotes.front();

  const double current_price = current_quote["currentPrice"];
  const double day_range = (double)reference_quote["highPrice"] -
                           (double)reference_quote["lowPrice"];
  const double tick_velocity_10 = speedometer.average_velocity(10).second;
  const double tick_velocity_30 = speedometer.average_velocity(30).second;

  double trailing_stop;
  double trailing_stop_price;

  if (close_order->action == order_action_t::SELL) {
    trailing_stop = compute_trailing_stop(day_range, open_order,
                                          tick_velocity_10, tick_velocity_30);

    trailing_stop_price =
        close_order->stop_price != -INFINITY && open_order->profit > 0
            ? std::max(close_order->stop_price, (current_price - trailing_stop))
            : open_order->execution_price - trailing_stop;
  } else if (close_order->action == order_action_t::BUY_TO_COVER) {
    trailing_stop = compute_trailing_stop(day_range, open_order,
                                          -tick_velocity_10, -tick_velocity_30);

    trailing_stop_price =
        close_order->stop_price != INFINITY && open_order->profit > 0
            ? std::min(close_order->stop_price, (current_price + trailing_stop))
            : open_order->execution_price + trailing_stop;
  }

  std::cout << stream_format.bold << stream_format.cyan << std::endl;
  std::cout << "Trailing Stop: " << trailing_stop << std::endl;
  std::cout << stream_format.reset;

  close_order->stop_price = trailing_stop_price;
}

#endif

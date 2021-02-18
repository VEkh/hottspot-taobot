#if !defined ETRADE__STRADDLE_set_trailing_stop_price
#define ETRADE__STRADDLE_set_trailing_stop_price

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include "straddle.h"        // ETrade::Straddle, order_t, quote, stream_format
#include <algorithm>         // std::max, std::min
#include <iostream>          // std::cout, std::endl
#include <math.h>            // INFINITY

const double LOSS_TRAILING_STOP_RATIO = 0.004;
const double SECURE_PROFIT_DAY_RANGE_RATIO = 0;

double compute_trailing_stop(const double day_range, const order_t *open_order,
                             const double ten_tick_velocity) {
  const double secure_profit = SECURE_PROFIT_DAY_RANGE_RATIO * day_range;

  if (open_order->profit < secure_profit) {
    return LOSS_TRAILING_STOP_RATIO * open_order->execution_price;
  }

  const double x = open_order->profit;
  const double x_shift = 1 - secure_profit;
  const double y_multiplier = 1 + (ten_tick_velocity * 100);

  return y_multiplier * log10(x + x_shift);
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
  const double ten_tick_velocity = speedometer.average_velocity(10).second;

  double trailing_stop;
  double trailing_stop_price;

  if (close_order->action == order_action_t::SELL) {
    trailing_stop =
        compute_trailing_stop(day_range, open_order, ten_tick_velocity);

    trailing_stop_price =
        close_order->stop_price != -INFINITY
            ? std::max(close_order->stop_price, (current_price - trailing_stop))
            : open_order->execution_price - trailing_stop;
  } else if (close_order->action == order_action_t::BUY_TO_COVER) {
    trailing_stop =
        compute_trailing_stop(day_range, open_order, -ten_tick_velocity);

    trailing_stop_price =
        close_order->stop_price != INFINITY
            ? std::min(close_order->stop_price, (current_price + trailing_stop))
            : open_order->execution_price + trailing_stop;
  }

  std::cout << stream_format.bold << stream_format.cyan << std::endl;
  std::cout << "Trailing Stop: " << trailing_stop << std::endl;
  std::cout << stream_format.reset;

  close_order->stop_price = trailing_stop_price;
}

#endif

#if !defined ETRADE__STRADDLE_set_trailing_stop_price
#define ETRADE__STRADDLE_set_trailing_stop_price

/*
 * ETrade::Straddle
 * day_range
 * order_t
 * quote
 * stream_format
 */
#include "straddle.h"

#include "compute_trailing_stop.cpp" // compute_trailing_stop
#include "etrade/deps.cpp"           // json
#include "lib/formatted.cpp"         // Formatted
#include <algorithm>                 // std::max, std::min
#include <iostream>                  // std::cout, std::endl
#include <math.h>                    // INFINITY

void ETrade::Straddle::set_trailing_stop_price(order_t *close_order,
                                               const order_t *open_order) {
  const double execution_price = open_order->execution_price;

  if (!execution_price) {
    return;
  }

  json current_quote = quotes.back();

  const double current_price = current_quote["currentPrice"];
  const double tick_velocity = speedometer.average_velocity(10).second;

  double trailing_stop;
  double trailing_stop_price;

  if (close_order->action == order_action_t::SELL) {
    trailing_stop = compute_trailing_stop(open_order, tick_velocity);

    trailing_stop_price =
        close_order->stop_price != -INFINITY && open_order->profit > 0
            ? std::max(close_order->stop_price, (current_price - trailing_stop))
            : open_order->execution_price - trailing_stop;
  } else if (close_order->action == order_action_t::BUY_TO_COVER) {
    trailing_stop = compute_trailing_stop(open_order, -tick_velocity);

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

#if !defined ETRADE__STOCK_BOT_set_trailing_stop_price
#define ETRADE__STOCK_BOT_set_trailing_stop_price

/*
 * ETrade::StockBot
 * day_range
 * order_t
 * quote
 * quote_t
 * stream_format
 */
#include "stock_bot.h"

#include "compute_trailing_stop.cpp" // compute_trailing_stop
#include "lib/formatted.cpp"         // Formatted
#include <algorithm>                 // std::max, std::min
#include <iostream>                  // std::cout, std::endl
#include <math.h>                    // INFINITY

void ETrade::StockBot::set_trailing_stop_price(order_t *close_order,
                                               const order_t *open_order) {
  const double execution_price = open_order->execution_price;

  if (!execution_price) {
    return;
  }

  quote_t current_quote = quotes.back();

  const double current_price = current_quote.current_price;
  const double sma_price = simple_moving_average;
  const double tick_velocity = speedometer.average_velocity(10).second;

  double sma_trailing_stop;
  double sma_trailing_stop_price;
  double trailing_stop;
  double trailing_stop_price;

  if (close_order->action == order_action_t::SELL) {
    trailing_stop = compute_trailing_stop(open_order->profit, tick_velocity);
    sma_trailing_stop =
        compute_trailing_stop(open_order->sma_profit, tick_velocity);

    trailing_stop_price =
        close_order->stop_price != -INFINITY && open_order->profit > 0
            ? std::max(close_order->stop_price, (current_price - trailing_stop))
            : open_order->execution_price - trailing_stop;

    sma_trailing_stop_price =
        close_order->sma_stop_price != -INFINITY && open_order->sma_profit > 0
            ? std::max(close_order->sma_stop_price,
                       (sma_price - sma_trailing_stop))
            : open_order->sma_execution_price - sma_trailing_stop;
  } else if (close_order->action == order_action_t::BUY_TO_COVER) {
    trailing_stop = compute_trailing_stop(open_order->profit, -tick_velocity);
    sma_trailing_stop =
        compute_trailing_stop(open_order->sma_profit, -tick_velocity);

    trailing_stop_price =
        close_order->stop_price != INFINITY && open_order->profit > 0
            ? std::min(close_order->stop_price, (current_price + trailing_stop))
            : open_order->execution_price + trailing_stop;

    sma_trailing_stop_price =
        close_order->sma_stop_price != INFINITY && open_order->sma_profit > 0
            ? std::min(close_order->sma_stop_price,
                       (sma_price + sma_trailing_stop))
            : open_order->sma_execution_price + sma_trailing_stop;
  }

  std::cout << stream_format.bold << stream_format.cyan << std::endl;
  std::cout << "Trailing Stop: " << trailing_stop << std::endl;
  std::cout << "SMA Trailing Stop: " << sma_trailing_stop << std::endl;
  std::cout << stream_format.reset;

  close_order->stop_price = trailing_stop_price;
  close_order->sma_stop_price = sma_trailing_stop_price;
}

#endif

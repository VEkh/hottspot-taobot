#if !defined ETRADE__STRADDLE_set_trailing_stop_price
#define ETRADE__STRADDLE_set_trailing_stop_price

#include "etrade/deps.cpp" // json
#include "straddle.h"      // ETrade::Straddle, order_t, quote, stream_format
#include <algorithm>       // std::max, std::min
#include <iostream>        // std::cout, std::endl
#include <math.h>          // INFINITY

const double LOSS_TRAILING_STOP_RATIO = 0.002;
const double SECURE_PROFIT_PRICE = 0.50;

double compute_trailing_stop(const double open_execution_price,
                             const double profit) {
  if (profit <= SECURE_PROFIT_PRICE) {
    return LOSS_TRAILING_STOP_RATIO * open_execution_price;
  }

  return log10(profit + 1 + SECURE_PROFIT_PRICE);
}

void ETrade::Straddle::set_trailing_stop_price(order_t *close_order,
                                               const order_t *open_order) {
  double execution_price = open_order->execution_price;

  if (!execution_price) {
    return;
  }

  json current_quote = quotes.back();

  double current_price = current_quote["currentPrice"];

  double trailing_stop =
      compute_trailing_stop(execution_price, open_order->profit);

  double trailing_stop_price;

  if (close_order->action == order_action_t::SELL) {
    trailing_stop_price =
        close_order->stop_price != -INFINITY
            ? std::max(close_order->stop_price, (current_price - trailing_stop))
            : open_order->execution_price - trailing_stop;
  } else if (close_order->action == order_action_t::BUY_TO_COVER) {
    trailing_stop_price =
        close_order->stop_price != INFINITY
            ? std::min(close_order->stop_price, (current_price + trailing_stop))
            : open_order->execution_price + trailing_stop;
  }

  std::cout << stream_format.bold << stream_format.cyan << std::endl;
  std::cout << "Trailing Stop Magnitude: " << trailing_stop << std::endl;
  std::cout << stream_format.reset;

  close_order->stop_price = trailing_stop_price;
}

#endif

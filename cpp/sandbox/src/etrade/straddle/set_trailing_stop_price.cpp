#if !defined ETRADE__STRADDLE_set_trailing_stop_price
#define ETRADE__STRADDLE_set_trailing_stop_price

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "straddle.h"             // ETrade::Straddle, order_t, quote
#include <algorithm>              // std::max, std::min
#include <math.h>                 // INFINITY

double TRAILING_STOP_PERCENT = 0.002;

void ETrade::Straddle::set_trailing_stop_price(order_t &close_order,
                                               const order_t &open_order) {
  double execution_price = open_order.execution_price;

  if (!execution_price) {
    return;
  }

  json current_quote = quotes.back();

  double beta = current_quote["beta"];
  double current_price = current_quote["currentPrice"];
  double trailing_stop = TRAILING_STOP_PERCENT * beta * execution_price;
  double trailing_stop_price;

  if (close_order.action == order_action_t::SELL) {
    trailing_stop_price =
        close_order.stop_price != -INFINITY
            ? std::max(close_order.stop_price, (current_price - trailing_stop))
            : open_order.execution_price - trailing_stop;
  } else if (close_order.action == order_action_t::BUY_TO_COVER) {
    trailing_stop_price =
        close_order.stop_price != INFINITY
            ? std::min(close_order.stop_price, (current_price + trailing_stop))
            : open_order.execution_price + trailing_stop;
  }

  close_order.stop_price = trailing_stop_price;
}

#endif

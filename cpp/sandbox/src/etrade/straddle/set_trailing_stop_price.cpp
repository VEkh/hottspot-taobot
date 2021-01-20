#if !defined ETRADE__STRADDLE_set_trailing_stop_price
#define ETRADE__STRADDLE_set_trailing_stop_price

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "straddle.h"             // ETrade::Straddle, order_t, quote
#include <algorithm>              // std::max, std::min
#include <math.h>                 // INFINITY

double LOSS_TRAILING_STOP_RATIO = 0.002;
double PROFIT_THRESHOLD = 0.001;
double PROFIT_TRAILING_STOP_RATIO = 0.0005;

void ETrade::Straddle::set_trailing_stop_price(order_t *close_order,
                                               const order_t *open_order) {
  double execution_price = open_order->execution_price;

  if (!execution_price) {
    return;
  }

  json current_quote = quotes.back();

  double beta = current_quote["beta"];
  double current_price = current_quote["currentPrice"];
  double profit_threshold = execution_price * PROFIT_THRESHOLD;

  double loss_trailing_stop = LOSS_TRAILING_STOP_RATIO * beta * execution_price;
  double profit_trailing_stop = PROFIT_TRAILING_STOP_RATIO * execution_price;

  double profit = close_order->action == order_action_t::SELL
                      ? current_price - execution_price
                      : execution_price - current_price;

  double trailing_stop =
      profit >= profit_threshold ? profit_trailing_stop : loss_trailing_stop;

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

  close_order->stop_price = trailing_stop_price;
}

#endif

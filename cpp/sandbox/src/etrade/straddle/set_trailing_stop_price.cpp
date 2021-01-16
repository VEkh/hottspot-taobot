#if !defined ETRADE__STRADDLE_set_trailing_stop_price
#define ETRADE__STRADDLE_set_trailing_stop_price

#include "straddle.h" // ETrade::Straddle, day_range, order_t, quote
#include <algorithm>  // std::max, std::min
#include <math.h>     // INFINITY

double PROFIT_THRESHOLD_DAY_RANGE_RATIO = 0.02;

void ETrade::Straddle::set_trailing_stop_price(order_t &close_order,
                                               const order_t &open_order) {
  if (!open_order.execution_price) {
    return;
  }

  const char *order_action = ORDER_ACTIONS[open_order.action];
  double current_price = quote["currentPrice"];
  double profit_threshold = PROFIT_THRESHOLD_DAY_RANGE_RATIO * day_range;
  double trailing_limit_price;
  double trailing_stop_price;

  double trailing_limit_day_range_ratio =
      open_order.profit > profit_threshold ? 0.01 : INFINITY;

  double trailing_stop_day_range_ratio =
      open_order.profit > profit_threshold ? 0.005 : INFINITY;

  double trailing_limit = day_range * trailing_limit_day_range_ratio;
  double trailing_stop = day_range * trailing_stop_day_range_ratio;

  if (close_order.action == order_action_t::SELL) {
    trailing_limit_price = close_order.limit_price != -INFINITY
                               ? std::max(close_order.limit_price,
                                          (current_price - trailing_limit))
                               : open_order.execution_price - trailing_limit;

    trailing_stop_price =
        close_order.stop_price != -INFINITY
            ? std::max(close_order.stop_price, (current_price - trailing_stop))
            : open_order.execution_price - trailing_stop;

  } else if (close_order.action == order_action_t::BUY_TO_COVER) {
    trailing_limit_price = close_order.limit_price != INFINITY
                               ? std::min(close_order.limit_price,
                                          (current_price + trailing_limit))
                               : open_order.execution_price + trailing_limit;

    trailing_stop_price =
        close_order.stop_price != INFINITY
            ? std::min(close_order.stop_price, (current_price + trailing_stop))
            : open_order.execution_price + trailing_stop;
  }

  close_order.stop_price = trailing_stop_price;
  close_order.limit_price = trailing_limit_price;
}

#endif

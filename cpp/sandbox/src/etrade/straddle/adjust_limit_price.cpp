#if !defined ETRADE__STRADDLE_adjust_limit_price
#define ETRADE__STRADDLE_adjust_limit_price

#include "etrade/deps.cpp"    // json
#include "get_order_json.cpp" // get_order_json
#include "lib/formatted.cpp"  // Formatted
#include "straddle.h"         // ETrade::Straddle, order_t
#include <cmath>              // abs

void ETrade::Straddle::adjust_limit_price(order_t &close_order,
                                          const order_t &open_order) {
  if (close_order.adjusted_limit_price || !open_order.execution_price) {
    return;
  }

  double profit = abs(close_order.limit_price - open_order.limit_price);

  if (close_order.action == order_action_t::SELL &&
      open_order.execution_price > open_order.limit_price) {
    close_order.adjusted_limit_price = close_order.execution_price + profit;
  } else if (close_order.action == order_action_t::BUY_TO_COVER &&
             open_order.execution_price < open_order.limit_price) {
    close_order.adjusted_limit_price = close_order.execution_price - profit;
  }
}

#endif

#if !defined ETRADE__STRADDLE_set_profit
#define ETRADE__STRADDLE_set_profit

#include "straddle.h" // ETrade::Straddle, order_t, quote

void ETrade::Straddle::set_profit(order_t &order) {
  double current_price = quote["currentPrice"];
  double profit;

  bool is_long_position = order.action == order_action_t::BUY ||
                          order.action == order_action_t::SELL;

  bool is_short_position = order.action == order_action_t::SELL_SHORT ||
                           order.action == order_action_t::BUY_TO_COVER;

  if (is_long_position) {
    profit = current_price - order.execution_price;
  } else if (is_short_position) {
    profit = order.execution_price - current_price;
  }

  order.profit = profit;
}

#endif

#if !defined ETRADE__STRADDLE_set_profit
#define ETRADE__STRADDLE_set_profit

#include "straddle.h" // ETrade::Straddle, order_t, quotes

void ETrade::Straddle::set_profit(order_t *order) {
  double current_price = quotes.back()["currentPrice"];
  double profit;

  bool is_long_position = order->action == order_action_t::BUY;
  bool is_short_position = order->action == order_action_t::SELL_SHORT;

  if (is_long_position) {
    profit = current_price - order->execution_price;
  } else if (is_short_position) {
    profit = order->execution_price - current_price;
  }

  order->profit = profit;
}

void ETrade::Straddle::set_profit(order_t *close_order,
                                  const order_t *open_order) {
  double profit;

  bool is_long_position = close_order->action == order_action_t::SELL;
  bool is_short_position = close_order->action == order_action_t::BUY_TO_COVER;

  if (is_long_position) {
    profit = close_order->execution_price - open_order->execution_price;
  } else if (is_short_position) {
    profit = open_order->execution_price - close_order->execution_price;
  }

  close_order->profit = profit;
}

#endif

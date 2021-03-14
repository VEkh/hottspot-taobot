#if !defined ETRADE__STOCK_BOT_set_profit
#define ETRADE__STOCK_BOT_set_profit

#include "is_long_side.cpp" // is_long_side
#include "stock_bot.h"      // ETrade::StockBot, order_t

void ETrade::StockBot::set_profit(order_t *order) {
  const double current_price = this->quotes.back().current_price;
  double profit;

  bool is_long_side_ = is_long_side(order);

  if (is_long_side_) {
    profit = current_price - order->execution_price;
  } else {
    profit = order->execution_price - current_price;
  }

  order->profit = profit;
}

void ETrade::StockBot::set_profit(order_t *close_order,
                                  const order_t *open_order) {
  double profit;

  bool is_long_side_ = is_long_side(close_order);

  if (is_long_side_) {
    profit = close_order->execution_price - open_order->execution_price;
  } else {
    profit = open_order->execution_price - close_order->execution_price;
  }

  close_order->profit = profit;
}

#endif

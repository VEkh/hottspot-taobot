#ifndef ETRADE__STOCK_BOT_set_profit
#define ETRADE__STOCK_BOT_set_profit

#include "stock_bot.h" // ETrade::StockBot, order_t
#include <algorithm>   // std::max
#include <time.h>      // time time_t

void ETrade::StockBot::set_profit(order_t *order) {
  const double current_price = this->quotes.back().current_price;

  double profit;

  if (this->is_long_position) {
    profit = current_price - order->execution_price;
  } else {
    profit = order->execution_price - current_price;
  }

  if (profit >= order->max_profit || !order->max_profit_timestamp) {
    time_t now;
    time(&now);

    order->max_profit_timestamp = now;
  }

  order->max_profit = std::max(profit, order->max_profit);
  order->profit = profit;
}

void ETrade::StockBot::set_profit(order_t *close_order,
                                  const order_t *open_order) {

  double profit;

  if (this->is_long_position) {
    profit = close_order->execution_price - open_order->execution_price;
  } else {
    profit = open_order->execution_price - close_order->execution_price;
  }

  close_order->profit = profit;
}

#endif

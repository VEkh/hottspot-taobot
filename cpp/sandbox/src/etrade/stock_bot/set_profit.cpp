#if !defined ETRADE__STOCK_BOT_set_profit
#define ETRADE__STOCK_BOT_set_profit

#include "compute_normalizing_ratio.cpp" // compute_normalizing_ratio
#include "stock_bot.h"                   // ETrade::StockBot, order_t

void ETrade::StockBot::set_profit(order_t *order) {
  const double current_price = this->quotes.back().current_price;
  const double normalizing_ratio =
      compute_normalizing_ratio(order->execution_price);

  double profit;

  if (this->is_long_position) {
    profit = current_price - order->execution_price;
  } else {
    profit = order->execution_price - current_price;
  }

  order->normalized_profit = normalizing_ratio * profit;
  order->profit = profit;
}

void ETrade::StockBot::set_profit(order_t *close_order,
                                  const order_t *open_order) {
  const double normalizing_ratio =
      compute_normalizing_ratio(open_order->execution_price);

  double profit;

  if (this->is_long_position) {
    profit = close_order->execution_price - open_order->execution_price;
  } else {
    profit = open_order->execution_price - close_order->execution_price;
  }

  close_order->normalized_profit = normalizing_ratio * profit;
  close_order->profit = profit;
}

#endif

#ifndef ETRADE__STOCK_BOT_compute_profit
#define ETRADE__STOCK_BOT_compute_profit

/*
 * ETrade::StockBot
 * order_t
 * quote_t
 */
#include "stock_bot.h"

double ETrade::StockBot::compute_profit(const order_t *order,
                                        const quote_t *quote) {
  const double current_price = quote->current_price;

  if (this->is_long_position) {
    return current_price - order->execution_price;
  }

  return order->execution_price - current_price;
}

double ETrade::StockBot::compute_profit(const order_t *close_order,
                                        const order_t *open_order) {
  if (this->is_long_position) {
    return close_order->execution_price - open_order->execution_price;
  }

  return open_order->execution_price - close_order->execution_price;
}

#endif

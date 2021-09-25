#ifndef ETRADE__TAO_BOT_compute_profit
#define ETRADE__TAO_BOT_compute_profit

/*
 * ETrade::TaoBot
 * order_t
 * quote_t
 */
#include "tao_bot.h"

double ETrade::TaoBot::compute_profit(const order_t *order,
                                      const quote_t *quote) {
  const double price = quote->price;

  if (this->is_long_position) {
    return price - order->execution_price;
  }

  return order->execution_price - price;
}

double ETrade::TaoBot::compute_profit(const order_t *close_order,
                                      const order_t *open_order) {
  if (this->is_long_position) {
    return close_order->execution_price - open_order->execution_price;
  }

  return open_order->execution_price - close_order->execution_price;
}

#endif

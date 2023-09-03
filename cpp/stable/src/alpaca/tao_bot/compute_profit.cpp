#ifndef ALPACA__TAO_BOT_compute_profit
#define ALPACA__TAO_BOT_compute_profit

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, order_t, quote_t

double Alpaca::TaoBot::compute_profit(const order_t *order,
                                      const quote_t *quote) {
  const double price = quote->price;

  if (order->action == order_action_t::BUY) {
    return price - order->execution_price;
  }

  return order->execution_price - price;
}

double Alpaca::TaoBot::compute_profit(const order_t *close_order_,
                                      const order_t *open_order_) {
  if (open_order_->action == order_action_t::BUY) {
    return close_order_->execution_price - open_order_->execution_price;
  }

  return open_order_->execution_price - close_order_->execution_price;
}

#endif

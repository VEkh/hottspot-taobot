#ifndef ALPACA__TAO_BOT_open_position_profit
#define ALPACA__TAO_BOT_open_position_profit

#include "tao_bot.h" // Alpaca::TaoBot, order_t

double Alpaca::TaoBot::open_position_profit(
    const order_t *base_open_order, const order_t *hedge_open_order = nullptr) {
  double total = base_open_order->profit * base_open_order->quantity;

  if (hedge_open_order) {
    total += hedge_open_order->profit * hedge_open_order->quantity;
  }

  return total;
}

#endif

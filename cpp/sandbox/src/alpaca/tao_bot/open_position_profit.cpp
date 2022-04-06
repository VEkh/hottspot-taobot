#ifndef ALPACA__TAO_BOT_open_position_profit
#define ALPACA__TAO_BOT_open_position_profit

#include "tao_bot.h" // Alpaca::TaoBot, order_t

double Alpaca::TaoBot::open_position_profit(const order_t *base_open_order,
                                            const order_t *hedge_open_order) {
  const double base_profit =
      base_open_order->profit * base_open_order->quantity;

  const double hedge_profit =
      hedge_open_order->profit * hedge_open_order->quantity;

  return base_profit + hedge_profit;
}

#endif

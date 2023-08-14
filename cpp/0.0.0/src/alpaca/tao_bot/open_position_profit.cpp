#ifndef ALPACA__TAO_BOT_open_position_profit
#define ALPACA__TAO_BOT_open_position_profit

#include "tao_bot.h" // Alpaca::TaoBot, order_t

double Alpaca::TaoBot::open_position_profit(const order_t *order_ptr) {
  double total = order_ptr->profit * order_ptr->quantity;

  return total;
}

#endif

#ifndef OANDA__TAO_BOT_open_position_profit
#define OANDA__TAO_BOT_open_position_profit

#include "tao_bot.h" // Oanda::TaoBot, order_t

double Oanda::TaoBot::open_position_profit(const order_t *order_ptr) {
  return order_ptr->profit * order_ptr->quantity;
}

#endif

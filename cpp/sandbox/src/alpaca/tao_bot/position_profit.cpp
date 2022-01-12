#ifndef ALPACA__TAO_BOT_position_profit
#define ALPACA__TAO_BOT_position_profit

/*
 * Alpaca::TaoBot
 * position_t
 */
#include "tao_bot.h"

double Alpaca::TaoBot::position_profit(const position_t &position) {
  return position.close_order.profit * position.close_order.quantity;
}

#endif

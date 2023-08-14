#ifndef ALPACA__TAO_BOT_closed_position_profit
#define ALPACA__TAO_BOT_closed_position_profit

/*
 * Alpaca::TaoBot
 * position_t
 */
#include "tao_bot.h"

double Alpaca::TaoBot::closed_position_profit(const position_t &position) {
  return position.close_order.profit * position.close_order.quantity;
}

#endif

#ifndef OANDA__TAO_BOT_closed_position_profit
#define OANDA__TAO_BOT_closed_position_profit

/*
 * Oanda::TaoBot
 * position_t
 */
#include "tao_bot.h"

double Oanda::TaoBot::closed_position_profit(const position_t &position) {
  return position.close_order.profit * position.close_order.quantity;
}

#endif

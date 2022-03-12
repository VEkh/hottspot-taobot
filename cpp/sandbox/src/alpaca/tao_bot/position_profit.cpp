#ifndef ALPACA__TAO_BOT_position_profit
#define ALPACA__TAO_BOT_position_profit

/*
 * Alpaca::TaoBot
 * position_t
 */
#include "tao_bot.h"

double Alpaca::TaoBot::position_profit(const position_t &position) {
  const double profit =
      position.close_order.profit * position.close_order.quantity;

  const double hedge_profit =
      position.hedge_close_order.profit * position.hedge_close_order.quantity;

  return hedge_profit + profit;
}

#endif

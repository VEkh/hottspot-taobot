#ifndef ALPACA__TAO_BOT_order_win_result
#define ALPACA__TAO_BOT_order_win_result

/*
 * Alpaca::TaoBot
 * order_t
 * order_win_result_t
 */
#include "tao_bot.h"

#include "position_profit.cpp" // position_profit

Alpaca::TaoBot::order_win_result_t
Alpaca::TaoBot::order_win_result(const position_t position) {
  const double profit = position_profit(position);

  if (profit > 0) {
    return order_win_result_t::WIN;
  }

  if (profit == 0) {
    return order_win_result_t::TIE;
  }

  return order_win_result_t::LOSS;
}

#endif

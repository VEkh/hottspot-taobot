#ifndef OANDA__TAO_BOT_order_win_result
#define OANDA__TAO_BOT_order_win_result

/*
 * Oanda::TaoBot
 * order_t
 * order_win_result_t
 */
#include "tao_bot.h"

#include "closed_position_profit.cpp" // closed_position_profit

Oanda::TaoBot::order_win_result_t
Oanda::TaoBot::order_win_result(const position_t position) {
  const double profit = closed_position_profit(position);

  if (profit > 0) {
    return order_win_result_t::WIN;
  }

  if (profit == 0) {
    return order_win_result_t::TIE;
  }

  return order_win_result_t::LOSS;
}

#endif

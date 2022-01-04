#ifndef ALPACA__TAO_BOT_order_win_result
#define ALPACA__TAO_BOT_order_win_result

/*
 * Alpaca::TaoBot
 * order_t
 * order_win_result_t
 */
#include "tao_bot.h"

Alpaca::TaoBot::order_win_result_t
Alpaca::TaoBot::order_win_result(const order_t *order) {
  if (order->profit > 0) {
    return order_win_result_t::WIN;
  }

  if (order->profit == 0) {
    return order_win_result_t::TIE;
  }

  return order_win_result_t::LOSS;
}

#endif

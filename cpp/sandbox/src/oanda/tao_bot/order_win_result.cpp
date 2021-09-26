#ifndef OANDA__TAO_BOT_order_win_result
#define OANDA__TAO_BOT_order_win_result

/*
 * Oanda::TaoBot
 * order_t
 * order_win_result_t
 */
#include "tao_bot.h"

Oanda::TaoBot::order_win_result_t
Oanda::TaoBot::order_win_result(const order_t *order) {
  if (order->profit > 0) {
    return order_win_result_t::WIN;
  }

  if (order->profit == 0) {
    return order_win_result_t::TIE;
  }

  return order_win_result_t::LOSS;
}

#endif

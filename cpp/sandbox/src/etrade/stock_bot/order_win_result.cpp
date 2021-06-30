#ifndef ETRADE__STOCK_BOT_order_win_result
#define ETRADE__STOCK_BOT_order_win_result

/*
 * ETrade::StockBot
 * order_t
 * order_win_result_t
 */
#include "stock_bot.h"

ETrade::StockBot::order_win_result_t
ETrade::StockBot::order_win_result(const order_t *order) {
  if (order->profit > 0) {
    return order_win_result_t::WIN;
  }

  if (order->profit == 0) {
    return order_win_result_t::TIE;
  }

  return order_win_result_t::LOSS;
}

#endif

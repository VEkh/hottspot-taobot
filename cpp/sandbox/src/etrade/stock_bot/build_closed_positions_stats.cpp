#ifndef ETRADE__STOCK_BOT_build_closed_positions_stats
#define ETRADE__STOCK_BOT_build_closed_positions_stats

/*
 * ETrade::StockBot
 * order_t
 * order_win_result_t
 * position_t
 */
#include "stock_bot.h"

#include "order_win_result.cpp" // order_win_result
#include <map>                  // std::map

ETrade::StockBot::closed_positions_stats_t
ETrade::StockBot::build_closed_positions_stats() {
  std::map<order_win_result_t, int> results = {
      {order_win_result_t::LOSS, 0},
      {order_win_result_t::TIE, 0},
      {order_win_result_t::WIN, 0},
  };

  double total_profit = 0.00;

  for (position_t position : this->closed_positions) {
    order_win_result_t result = order_win_result(&(position.close_order));
    results[result]++;
    total_profit += close_order.profit * close_order.quantity;
  }

  return {
      .results = results,
      .total_profit = total_profit,
  };
}

#endif

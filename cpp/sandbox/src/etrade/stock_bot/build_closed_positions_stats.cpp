#ifndef ETRADE__STOCK_BOT_build_closed_positions_stats
#define ETRADE__STOCK_BOT_build_closed_positions_stats

/*
 * ETrade::StockBot
 * order_t
 * position_result_t
 * position_t
 */
#include "stock_bot.h"

#include <map> // std::map

ETrade::StockBot::closed_positions_stats_t
ETrade::StockBot::build_closed_positions_stats() {
  std::map<position_result_t, int> results = {
      {position_result_t::LOSS, 0},
      {position_result_t::TIE, 0},
      {position_result_t::WIN, 0},
  };

  double total_profit = 0.00;

  for (position_t position : this->closed_positions) {
    order_t close_order = position.close_order;

    if (close_order.profit > 0) {
      results[position_result_t::WIN]++;
    } else if (close_order.profit == 0) {
      results[position_result_t::TIE]++;
    } else {
      results[position_result_t::LOSS]++;
    }

    total_profit += close_order.profit * close_order.quantity;
  }

  return {
      .results = results,
      .total_profit = total_profit,
  };
}

#endif

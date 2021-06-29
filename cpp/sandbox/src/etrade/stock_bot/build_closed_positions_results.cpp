#ifndef ETRADE__STOCK_BOT_build_closed_positions_results
#define ETRADE__STOCK_BOT_build_closed_positions_results

/*
 * ETrade::StockBot
 * order_t
 * position_result_t
 * position_t
 */
#include "stock_bot.h"

#include <map> // std::map

std::map<ETrade::StockBot::position_result_t, int>
ETrade::StockBot::build_closed_positions_results() {
  std::map<position_result_t, int> results = {
      {position_result_t::LOSS, 0},
      {position_result_t::TIE, 0},
      {position_result_t::WIN, 0},
  };

  for (position_t position : this->closed_positions) {
    order_t close_order = position.close_order;

    if (close_order.profit > 0) {
      results[position_result_t::WIN]++;
    } else if (close_order.profit == 0) {
      results[position_result_t::TIE]++;
    } else {
      results[position_result_t::LOSS]++;
    }
  }

  return results;
}

#endif

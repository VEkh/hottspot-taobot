#ifndef ETRADE__STOCK_BOT_max_losing_streak_loss
#define ETRADE__STOCK_BOT_max_losing_streak_loss

/*
 * ETrade::StockBot
 * order_win_result_t
 * position_t
 */
#include "stock_bot.h"

#include "order_win_result.cpp" // order_win_result
#include <algorithm>            // std::min
#include <math.h>               // INFINITY
#include <vector>               // std::vector

double ETrade::StockBot::max_losing_streak_loss() {
  double max_loss = INFINITY;

  std::vector<position_t>::reverse_iterator it;

  for (it = this->closed_positions.rbegin();
       it != this->closed_positions.rend() &&
       order_win_result(&(it->close_order)) == order_win_result_t::LOSS;
       it++) {
    max_loss = std::min(max_loss, it->close_order.profit);
  }

  return max_loss;
}

#endif

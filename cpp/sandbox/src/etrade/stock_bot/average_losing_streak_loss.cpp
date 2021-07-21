#ifndef ETRADE__STOCK_BOT_average_losing_streak_loss
#define ETRADE__STOCK_BOT_average_losing_streak_loss

/*
 * ETrade::StockBot
 * order_win_result_t
 * position_t
 */
#include "stock_bot.h"

#include "order_win_result.cpp" // order_win_result
#include <vector>               // std::vector

double ETrade::StockBot::average_losing_streak_loss() {
  std::vector<position_t>::reverse_iterator it;
  double sum = 0;
  int count = 0;

  for (it = this->closed_positions.rbegin();
       it != this->closed_positions.rend() &&
       order_win_result(&(it->close_order)) == order_win_result_t::LOSS;
       it++) {
    sum += it->close_order.profit;
    count++;
  }

  return count ? sum / count : 0;
}

#endif

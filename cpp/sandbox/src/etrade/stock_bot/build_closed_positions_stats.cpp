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
#include <algorithm>            // std::max
#include <map>                  // std::map

ETrade::StockBot::closed_positions_stats_t
ETrade::StockBot::build_closed_positions_stats() {
  std::map<order_win_result_t, int> results = {
      {order_win_result_t::LOSS, 0},
      {order_win_result_t::TIE, 0},
      {order_win_result_t::WIN, 0},
  };

  bool loss_streak_broken = false;
  bool win_streak_broken = false;
  double total_profit = 0.00;
  int l = this->closed_positions.size();
  int loss_streak = 0;
  int win_streak = 0;

  order_win_result_t current_streak_type = order_win_result_t::WIN;

  int current_streak_count = 0;

  std::map<order_win_result_t, int> max_streaks = {
      {order_win_result_t::LOSS, 0},
      {order_win_result_t::WIN, 0},
  };

  for (int i = l - 1; i > -1; i--) {
    const position_t position = this->closed_positions[i];
    const order_win_result_t result = order_win_result(&(position.close_order));
    results[result]++;
    total_profit += position.close_order.profit * position.close_order.quantity;

    loss_streak_broken =
        loss_streak_broken || result == order_win_result_t::WIN;

    win_streak_broken = win_streak_broken || result == order_win_result_t::LOSS;

    if (result == order_win_result_t::WIN && !win_streak_broken) {
      win_streak++;
    } else if (result == order_win_result_t::LOSS && !loss_streak_broken) {
      loss_streak++;
    }

    if (result == current_streak_type) {
      current_streak_count++;

      max_streaks[current_streak_type] =
          std::max(max_streaks[current_streak_type], current_streak_count);
    } else {
      max_streaks[current_streak_type] =
          std::max(max_streaks[current_streak_type], current_streak_count);

      current_streak_type = result;
      current_streak_count = 1;
    }
  }

  return {
      .longest_loss_streak = max_streaks[order_win_result_t::LOSS],
      .longest_win_streak = max_streaks[order_win_result_t::WIN],
      .loss_streak = loss_streak,
      .results = results,
      .total_profit = total_profit,
      .win_streak = win_streak,
  };
}

#endif

#ifndef ETRADE__STOCK_BOT_build_closed_positions_stats
#define ETRADE__STOCK_BOT_build_closed_positions_stats

/*
 * ETrade::StockBot
 * order_t
 * order_win_result_t
 * order_win_result_streak_t
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

  order_win_result_t current_streak_type;

  int current_streak_count = 0;

  std::map<order_win_result_t, order_win_result_streak_t> streaks = {
      {
          order_win_result_t::LOSS,
          {.counts = {}, .current = 0, .longest = 0},
      },
      {
          order_win_result_t::WIN,
          {.counts = {}, .current = 0, .longest = 0},
      },
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
      streaks[order_win_result_t::WIN].current++;
    } else if (result == order_win_result_t::LOSS && !loss_streak_broken) {
      streaks[order_win_result_t::LOSS].current++;
    }

    if (i == l - 1) {
      current_streak_type = result;
    }

    if (result == current_streak_type) {
      current_streak_count++;
    }

    streaks[current_streak_type].longest =
        std::max(streaks[current_streak_type].longest, current_streak_count);

    if (result != current_streak_type || i == 0) {
      int streak_count =
          streaks[current_streak_type].counts[current_streak_count];

      streaks[current_streak_type].counts[current_streak_count] =
          streak_count ? streak_count + 1 : 1;
    }

    if (result != current_streak_type) {
      current_streak_type = result;
      current_streak_count = 1;
    }
  }

  return {
      .loss_streaks = streaks[order_win_result_t::LOSS],
      .results = results,
      .total_profit = total_profit,
      .win_streaks = streaks[order_win_result_t::WIN],
  };
}

#endif

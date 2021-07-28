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

  int loss_streak_count = 0;
  int win_streak_count = 0;

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
    const position_t *next_position_ptr =
        i == 0 ? nullptr : &(this->closed_positions[i - 1]);
    const order_win_result_t result = order_win_result(&(position.close_order));

    results[result]++;
    total_profit += position.close_order.profit * position.close_order.quantity;

    if (result == order_win_result_t::WIN) {
      loss_streak_broken = true;
      loss_streak_count = 0;
      win_streak_count++;

      if (!win_streak_broken) {
        streaks[order_win_result_t::WIN].current++;
      }
    } else {
      loss_streak_count++;
      win_streak_broken = true;
      win_streak_count = 0;

      if (!loss_streak_broken) {
        streaks[order_win_result_t::LOSS].current++;
      }
    }

    if (loss_streak_count &&
        (!next_position_ptr ||
         order_win_result(&(next_position_ptr->close_order)) ==
             order_win_result_t::WIN)) {
      int streak_count =
          streaks[order_win_result_t::LOSS].counts[loss_streak_count];

      streaks[order_win_result_t::LOSS].counts[loss_streak_count] =
          streak_count ? streak_count + 1 : 1;

      streaks[order_win_result_t::LOSS].longest = std::max(
          streaks[order_win_result_t::LOSS].longest, loss_streak_count);
    } else if (win_streak_count &&
               (!next_position_ptr ||
                order_win_result(&(next_position_ptr->close_order)) ==
                    order_win_result_t::LOSS)) {
      int streak_count =
          streaks[order_win_result_t::WIN].counts[win_streak_count];

      streaks[order_win_result_t::WIN].counts[win_streak_count] =
          streak_count ? streak_count + 1 : 1;

      streaks[order_win_result_t::WIN].longest =
          std::max(streaks[order_win_result_t::WIN].longest, win_streak_count);
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

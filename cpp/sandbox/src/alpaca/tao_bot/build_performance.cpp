#ifndef ALPACA__TAO_BOT_build_performance
#define ALPACA__TAO_BOT_build_performance

/*
 * Alpaca::TaoBot
 * order_win_result_t
 * order_win_result_streak_t
 * position_t
 */
#include "tao_bot.h"

#include "compute_martingale_quantity.cpp" // compute_martingale_quantity
#include "is_hedging.cpp"                  // is_hedging
#include "max_affordable_quantity.cpp"     // max_affordable_quantity
#include "order_win_result.cpp"            // order_win_result
#include "position_profit.cpp"             // position_profit
#include <algorithm>                       // std::max
#include <map>                             // std::map

Alpaca::TaoBot::performance_t Alpaca::TaoBot::build_performance() {
  std::map<order_win_result_t, int> results = {
      {order_win_result_t::LOSS, 0},
      {order_win_result_t::TIE, 0},
      {order_win_result_t::WIN, 0},
  };

  bool loss_streak_broken = false;
  bool win_streak_broken = false;
  double current_balance = 0.00;
  double current_loss_streak_balance = 0.00;
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
    const order_win_result_t result = order_win_result(position);

    const double position_profit_ = position_profit(position);

    results[result]++;
    current_balance += position_profit_;

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
        current_loss_streak_balance += position_profit_;
        streaks[order_win_result_t::LOSS].current++;
      }
    }

    if (loss_streak_count &&
        (!next_position_ptr ||
         order_win_result(*next_position_ptr) == order_win_result_t::WIN)) {
      int streak_count =
          streaks[order_win_result_t::LOSS].counts[loss_streak_count];

      streaks[order_win_result_t::LOSS].counts[loss_streak_count] =
          streak_count ? streak_count + 1 : 1;

      streaks[order_win_result_t::LOSS].longest = std::max(
          streaks[order_win_result_t::LOSS].longest, loss_streak_count);
    } else if (win_streak_count &&
               (!next_position_ptr || order_win_result(*next_position_ptr) ==
                                          order_win_result_t::LOSS)) {
      int streak_count =
          streaks[order_win_result_t::WIN].counts[win_streak_count];

      streaks[order_win_result_t::WIN].counts[win_streak_count] =
          streak_count ? streak_count + 1 : 1;

      streaks[order_win_result_t::WIN].longest =
          std::max(streaks[order_win_result_t::WIN].longest, win_streak_count);
    }
  }

  bool are_funds_sufficient;
  bool is_position_open;

  if (is_hedging()) {
    are_funds_sufficient = true;
    is_position_open =
        (!!this->open_order_ptr &&
         this->open_order.status == order_status_t::ORDER_FILLED) &&
        (!!this->hedge_open_order_ptr &&
         this->hedge_open_order.status == order_status_t::ORDER_FILLED);
  } else {
    are_funds_sufficient =
        compute_martingale_quantity() < max_affordable_quantity();

    is_position_open = !!this->open_order_ptr &&
                       this->open_order.status == order_status_t::ORDER_FILLED;
  }

  return {
      .are_funds_sufficient = are_funds_sufficient,
      .closed_positions_count = (int)this->closed_positions.size(),
      .current_balance = current_balance,
      .current_loss_streak_balance = current_loss_streak_balance,
      .is_position_open = is_position_open,
      .loss_streaks = streaks[order_win_result_t::LOSS],
      .max_balance = std::max(current_balance, this->performance.max_balance),
      .results = results,
      .symbol = this->symbol,
      .win_streaks = streaks[order_win_result_t::WIN],
  };
}

#endif

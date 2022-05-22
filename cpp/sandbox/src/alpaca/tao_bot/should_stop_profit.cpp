#ifndef ALPACA__TAO_BOT_should_stop_profit
#define ALPACA__TAO_BOT_should_stop_profit

#include "closed_position_profit.cpp" // closed_position_profit
#include "order_win_result.cpp"       // order_win_result
#include "tao_bot.h"                  // Alpaca::TaoBot, order_win_result_t
#include <algorithm>                  // std::max

bool Alpaca::TaoBot::should_stop_profit() {
  if (!this->closed_positions.size()) {
    return false;
  }

  const double MIN_RUNTIME_SECONDS = 60 * 60;
  const position_t last_position = this->closed_positions.back();

  if (last_position.close_order.runtime < MIN_RUNTIME_SECONDS) {
    return false;
  }

  const double INIT_MIN_WIN_RATE = 0.51;
  const double WIN_RATE_TRAILING_STOP = 0.01;
  const int l = this->closed_positions.size();

  bool min_win_rate_first_exceeded = false;
  bool trailing_stop_exceeded = false;
  double min_win_rate = INIT_MIN_WIN_RATE - WIN_RATE_TRAILING_STOP;
  double running_loss_count = 0.00;
  double running_win_count = 0.00;
  double total_profit = 0.00;

  for (int i = 0; i < l; i++) {
    const position_t position = this->closed_positions[i];
    total_profit += closed_position_profit(position);

    switch (order_win_result(position)) {
    case order_win_result_t::LOSS: {
      running_loss_count++;
      break;
    }
    case order_win_result_t::WIN: {
      running_win_count++;
      break;
    }
    }

    if (position.close_order.runtime < MIN_RUNTIME_SECONDS) {
      continue;
    }

    const double win_rate =
        running_win_count / (running_win_count + running_loss_count);

    if (!min_win_rate_first_exceeded && win_rate >= INIT_MIN_WIN_RATE) {
      min_win_rate_first_exceeded = true;
      continue;
    }

    min_win_rate = std::max(min_win_rate, win_rate - WIN_RATE_TRAILING_STOP);

    if (min_win_rate_first_exceeded && win_rate <= min_win_rate &&
        total_profit > 0) {
      trailing_stop_exceeded = true;
      break;
    }
  }

  return trailing_stop_exceeded;
}

#endif

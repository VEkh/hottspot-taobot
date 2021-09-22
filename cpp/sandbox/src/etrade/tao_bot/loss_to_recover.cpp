#ifndef ETRADE__TAO_BOT_loss_to_recover
#define ETRADE__TAO_BOT_loss_to_recover

/*
 * ETrade::TaoBot
 * closed_positions_stats_t
 * position_t
 */
#include "tao_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats
#include <valarray>                         // std::valarray

double ETrade::TaoBot::loss_to_recover() {
  const closed_positions_stats_t stats = build_closed_positions_stats();
  const double current_loss_streak = stats.loss_streaks.current;

  double loss_streak_loss = 0;

  for (int i = 1, l = this->closed_positions.size();
       i < current_loss_streak + 1; i++) {
    const position_t position = this->closed_positions[l - i];
    loss_streak_loss +=
        position.close_order.quantity * position.close_order.profit;
  }

  std::valarray<double> losses = {0, loss_streak_loss, stats.total_profit};

  return losses.min();
}

#endif

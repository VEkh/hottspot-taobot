#ifndef ETRADE__STOCK_BOT_redemptive_max_loss
#define ETRADE__STOCK_BOT_redemptive_max_loss

/*
 * ETrade::StockBot
 * closed_positions_stats_t
 * position_t
 */
#include "stock_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats

double ETrade::StockBot::redemptive_max_loss() {
  const closed_positions_stats_t stats = build_closed_positions_stats();
  const double current_loss_streak = stats.loss_streaks.current;

  double total_loss = 0;

  for (int i = 1, l = this->closed_positions.size();
       i < current_loss_streak + 1; i++) {
    const position_t position = this->closed_positions[l - i];
    total_loss += position.close_order.quantity * position.close_order.profit;
  }

  return (1.05 * total_loss) / this->open_order.quantity;
}

#endif

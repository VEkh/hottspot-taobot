#ifndef ETRADE__STOCK_BOT_martingale_quantity_multiplier
#define ETRADE__STOCK_BOT_martingale_quantity_multiplier

/*
 * ETrade::StockBot
 * closed_positions_stats_t
 */
#include "stock_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats
#include "lib/utils/time.cpp"               // utils::time_
#include <math.h>                           // pow

int ETrade::StockBot::martingale_quantity_multiplier() {
  if (!this->FLAG_MARTINGALE) {
    return 1;
  }

  const closed_positions_stats_t stats = build_closed_positions_stats();
  const int adjusted_loss_streak = this->insufficient_funds_at_loss
                                       ? this->insufficient_funds_at_loss - 1
                                       : stats.loss_streaks.current;

  return pow(2, adjusted_loss_streak % this->MAX_ALLOWABLE_LOSS_STREAK);
}

#endif

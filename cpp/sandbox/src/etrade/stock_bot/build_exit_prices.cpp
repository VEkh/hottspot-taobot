#ifndef ETRADE__STOCK_BOT_build_exit_prices
#define ETRADE__STOCK_BOT_build_exit_prices

/*
 * ETrade::StockBot
 * closed_positions_stats_t
 * exit_prices_t
 * order_win_result_t
 * position_t
 */
#include "stock_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats
#include "lib/utils/time.cpp"               // utils::time_
#include "redemptive_max_loss.cpp"          // redemptive_max_loss
#include <algorithm>                        // std::max
#include <math.h>                           // abs

ETrade::StockBot::exit_prices_t ETrade::StockBot::build_exit_prices() {
  const closed_positions_stats_t stats = build_closed_positions_stats();

  const double max_loss_multiplier =
      (stats.loss_streaks.current < this->MAX_EXPECTED_LOSS_STREAK / 2) ? 20.0
                                                                        : 40.0;
  const double secured_profit_ratio = 0.8;

  double max_loss = -1 * max_loss_multiplier * this->average_tick_price_delta;

  if (stats.loss_streaks.current) {
    max_loss = -1 * std::max(abs(redemptive_max_loss()), abs(max_loss));
  }

  const double min_profit = abs(max_loss) / secured_profit_ratio;

  const double secure_profit_lower =
      (secured_profit_ratio - 0.2) * this->open_order.max_profit;

  const double secure_profit_upper =
      secured_profit_ratio * this->open_order.max_profit;

  return {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .secure_profit_lower = secure_profit_lower,
      .secure_profit_upper = secure_profit_upper,
  };
}

#endif

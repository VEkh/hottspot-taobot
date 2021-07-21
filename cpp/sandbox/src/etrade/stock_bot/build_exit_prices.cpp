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
#include "max_losing_streak_loss.cpp"       // max_losing_streak_loss
#include <math.h>                           // pow

ETrade::StockBot::exit_prices_t ETrade::StockBot::build_exit_prices() {
  const double trailing_stop = 0.2;
  const double secured_profit_ratio = 1 - trailing_stop;

  const double max_loss_multiplier = 15.0;
  const double min_profit_multiplier = 15.0 / secured_profit_ratio;

  double max_loss = -1 * max_loss_multiplier * this->average_tick_price_delta;
  double min_profit = min_profit_multiplier * this->average_tick_price_delta;

  if (this->FLAG_MARTINGALE && !utils::time_::is_early_day() &&
      !this->closed_positions.empty()) {
    const position_t last_position = this->closed_positions.back();
    const closed_positions_stats_t closed_position_stats =
        build_closed_positions_stats();

    const int loss_streak = closed_position_stats.loss_streak;

    if (loss_streak > 0) {
      max_loss = max_losing_streak_loss();

      if (loss_streak == 4) {
        max_loss *= 1.2;
      }

      min_profit = abs(max_loss) / secured_profit_ratio;
    }
  }

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

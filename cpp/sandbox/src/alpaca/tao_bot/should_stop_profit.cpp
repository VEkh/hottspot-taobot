#ifndef ALPACA__TAO_BOT_should_stop_profit
#define ALPACA__TAO_BOT_should_stop_profit

#include "closed_position_profit.cpp"  // closed_position_profit
#include "order_win_result.cpp"        // order_win_result
#include "tao_bot.h"                   // Alpaca::TaoBot, order_win_result_t
#include "target_daily_profit.cpp"     // target_daily_profit
#include "tradeable_symbols_count.cpp" // tradeable_symbols_count
#include <algorithm>                   // std::max

bool Alpaca::TaoBot::should_stop_profit() {
  const double current_balance = this->performance.current_balance;
  const double max_profit = this->performance.max_balance;
  const double max_loss =
      max_profit * (1 - this->TARGET_DAILY_PROFIT_TRAILING_STOP);
  const double min_profit =
      target_daily_profit() / (1 - this->TARGET_DAILY_PROFIT_TRAILING_STOP);

  return max_profit >= min_profit && current_balance >= target_daily_profit() &&
         current_balance < max_loss;
}

#endif

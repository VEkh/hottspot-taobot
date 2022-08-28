#ifndef ALPACA__TAO_BOT_target_daily_profit_trailing_stop
#define ALPACA__TAO_BOT_target_daily_profit_trailing_stop

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max, std::min

double Alpaca::TaoBot::target_daily_profit_trailing_stop() {
  const double base_trailing_stop = this->TARGET_DAILY_PROFIT_TRAILING_STOP;
  const double max_trailing_stop = 0.005;

  const double max_profit =
      this->account_balance.max_balance - this->account_balance.original_balance;

  const double max_profit_ratio =
      max_profit / this->account_balance.original_balance;

  const double expanded_trailing_stop =
      max_profit_ratio - (1 + this->TARGET_DAILY_PROFIT);

  const double expanded_base_trailing_stop =
      std::max(base_trailing_stop, expanded_trailing_stop);

  return std::min(expanded_base_trailing_stop, max_trailing_stop);
}

#endif

#ifndef OANDA__TAO_BOT_target_account_profit_trailing_stop
#define OANDA__TAO_BOT_target_account_profit_trailing_stop

#include "tao_bot.h"                 // Oanda::TaoBot
#include "target_account_profit.cpp" // target_account_profit
#include <algorithm>                 // std::max, std::min

double Oanda::TaoBot::target_account_profit_trailing_stop() {
  const double base_trailing_stop = this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP;
  const double max_trailing_stop = 0.005;

  const double max_profit = this->account_balance.max_balance -
                            this->account_balance.original_balance;

  const double max_profit_ratio =
      (max_profit / this->account_balance.original_balance) - 1;

  const double expanded_trailing_stop =
      max_profit_ratio - target_account_profit();

  const double expanded_base_trailing_stop =
      std::max(base_trailing_stop, expanded_trailing_stop);

  return std::min(expanded_base_trailing_stop, max_trailing_stop);
}

#endif

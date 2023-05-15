#ifndef ALPACA__TAO_BOT_account_profit_expanding_trailing_stop_ratio
#define ALPACA__TAO_BOT_account_profit_expanding_trailing_stop_ratio

#include "tao_bot.h"                       // Alpaca::TaoBot
#include "target_account_profit_ratio.cpp" // target_account_profit_ratio
#include <algorithm>                       // std::max, std::min

double Alpaca::TaoBot::account_profit_expanding_trailing_stop_ratio(
    const double max_profit) {
  const double base_trailing_stop = this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP;
  const double max_trailing_stop = 0.005;

  const double max_profit_ratio =
      max_profit / this->account_snapshot.original_equity;

  const double expanded_base_trailing_stop = std::max(
      base_trailing_stop, max_profit_ratio - target_account_profit_ratio());

  return std::min(expanded_base_trailing_stop, max_trailing_stop);
}

#endif

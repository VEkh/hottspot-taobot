#ifndef OANDA__TAO_BOT_account_profit_expanding_trailing_stop_ratio
#define OANDA__TAO_BOT_account_profit_expanding_trailing_stop_ratio

#include "tao_bot.h" // Oanda::TaoBot
#include <algorithm> // std::max, std::min

double Oanda::TaoBot::account_profit_expanding_trailing_stop_ratio(
    const double max_profit) {
  const double base_trailing_stop = this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP;
  const double max_trailing_stop = 0.01;

  const double session_max_profit_ratio =
      max_profit / this->account_snapshot.original_equity;

  const double expanded_base_trailing_stop =
      std::max(base_trailing_stop,
               session_max_profit_ratio - this->TARGET_ACCOUNT_PROFIT_RATIO);

  return std::min(expanded_base_trailing_stop, max_trailing_stop);
}

#endif

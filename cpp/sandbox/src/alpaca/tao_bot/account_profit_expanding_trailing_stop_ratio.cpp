#ifndef ALPACA__TAO_BOT_account_profit_expanding_trailing_stop_ratio
#define ALPACA__TAO_BOT_account_profit_expanding_trailing_stop_ratio

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max, std::min

double Alpaca::TaoBot::account_profit_expanding_trailing_stop_ratio(
    const double max_profit) {
  const double base_trailing_stop = this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP;
  const double max_trailing_stop = this->api_client.is_live() ? 0.0025 : 0.005;

  const double max_profit_ratio =
      max_profit / this->account_balance.original_balance;

  const double expanded_base_trailing_stop = std::max(
      base_trailing_stop, max_profit_ratio - this->TARGET_ACCOUNT_PROFIT_RATIO);

  return std::min(expanded_base_trailing_stop, max_trailing_stop);
}

#endif

#ifndef ALPACA__TAO_BOT_build_account_exit_prices
#define ALPACA__TAO_BOT_build_account_exit_prices

#include "tao_bot.h"               // Alpaca::TaoBot, order_win_result_t
#include "target_daily_profit.cpp" // target_daily_profit
#include "target_daily_profit_trailing_stop.cpp" // target_daily_profit_trailing_stop
#include <algorithm>                             // std::max

Alpaca::TaoBot::account_exit_prices_t
Alpaca::TaoBot::build_account_exit_prices() {
  const double current_balance = this->account_balance.balance;
  const double max_profit = this->account_balance.max_balance -
                            this->account_balance.original_balance;

  const double target_account_profit =
      target_daily_profit(this->TARGET_DAILY_PROFIT);

  const double target_max_profit = target_daily_profit(
      this->TARGET_DAILY_PROFIT + this->TARGET_DAILY_PROFIT_TRAILING_STOP);

  const double current_profit =
      current_balance - this->account_balance.original_balance;

  const double max_profit_ratio =
      max_profit / this->account_balance.original_balance;

  const double stop_loss_profit_ratio =
      std::max(this->TARGET_DAILY_PROFIT,
               max_profit_ratio - target_daily_profit_trailing_stop());

  const double stop_loss_profit = target_daily_profit(stop_loss_profit_ratio);

  return {
      .current_profit = current_profit,
      .max_profit = max_profit,
      .stop_loss_profit = stop_loss_profit,
      .target_account_profit = target_account_profit,
      .target_max_profit = target_max_profit,
  };
}

#endif

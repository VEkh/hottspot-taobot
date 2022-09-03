#ifndef OANDA__TAO_BOT_build_account_exit_prices
#define OANDA__TAO_BOT_build_account_exit_prices

#include "tao_bot.h"                 // Oanda::TaoBot, order_win_result_t
#include "target_account_profit.cpp" // target_account_profit
#include "target_account_profit_trailing_stop.cpp" // target_account_profit_trailing_stop
#include <algorithm>                               // std::max

Oanda::TaoBot::account_exit_prices_t
Oanda::TaoBot::build_account_exit_prices() {
  const double current_balance = this->account_balance.balance;
  const double max_profit = this->account_balance.max_balance -
                            this->account_balance.original_balance;

  const double target_profit =
      target_account_profit(this->TARGET_ACCOUNT_PROFIT);

  const double target_max_profit = target_account_profit(
      this->TARGET_ACCOUNT_PROFIT + this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP);

  const double current_profit =
      current_balance - this->account_balance.original_balance;

  const double max_profit_ratio =
      max_profit / this->account_balance.original_balance;

  const double stop_loss_profit_ratio =
      std::max(this->TARGET_ACCOUNT_PROFIT,
               max_profit_ratio - target_account_profit_trailing_stop());

  const double stop_loss_profit = target_account_profit(stop_loss_profit_ratio);

  return {
      .current_profit = current_profit,
      .max_profit = max_profit,
      .stop_loss_profit = stop_loss_profit,
      .target_account_profit = target_profit,
      .target_max_profit = target_max_profit,
  };
}

#endif

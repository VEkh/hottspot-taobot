#ifndef ALPACA__TAO_BOT_build_account_exit_prices
#define ALPACA__TAO_BOT_build_account_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max

Alpaca::TaoBot::account_exit_prices_t
Alpaca::TaoBot::build_account_exit_prices() {
  const double current_balance = this->account_balance.balance;
  const double max_profit = this->account_balance.max_balance -
                            this->account_balance.original_balance;
  const double target_profit_ratio = 0.0005;
  const double target_profit_trailing_stop = 0.01;

  const double target_profit_cash =
      this->account_balance.original_balance * target_profit_ratio;

  const double target_max_profit =
      this->account_balance.original_balance *
      (target_profit_ratio + target_profit_trailing_stop);

  const double current_profit =
      current_balance - this->account_balance.original_balance;

  const double max_profit_ratio =
      max_profit / this->account_balance.original_balance;

  const double stop_loss_profit_ratio = std::max(
      target_profit_ratio, max_profit_ratio - target_profit_trailing_stop);

  const double stop_loss_profit =
      this->account_balance.original_balance * stop_loss_profit_ratio;

  return {
      .current_profit = current_profit,
      .max_profit = max_profit,
      .stop_loss_profit = stop_loss_profit,
      .target_account_profit = target_profit_cash,
      .target_max_profit = target_max_profit,
  };
}

#endif

#ifndef ALPACA__TAO_BOT_build_account_exit_prices
#define ALPACA__TAO_BOT_build_account_exit_prices

#include "has_super_profited.cpp" // has_super_profited
#include "tao_bot.h"              // Alpaca::TaoBot
#include <valarray>               // std::valarray

Alpaca::TaoBot::account_exit_prices_t
Alpaca::TaoBot::build_account_exit_prices() {
  const double current_balance = this->account_balance.balance;
  const double max_profit = this->account_balance.max_balance -
                            this->account_balance.original_balance;

  const double target_profit_cash = this->account_balance.original_balance *
                                    this->TARGET_ACCOUNT_PROFIT_RATIO;

  const double target_max_profit = this->account_balance.original_balance *
                                   (this->TARGET_ACCOUNT_PROFIT_RATIO +
                                    this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP);

  const double current_profit =
      current_balance - this->account_balance.original_balance;

  const double max_profit_ratio =
      max_profit / this->account_balance.original_balance;

  const double overall_max_profit = this->account_balance.overall_max_balance -
                                    this->account_balance.original_balance;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_balance.original_balance;

  const std::valarray<double> stop_loss_profit_ratios = {
      this->TARGET_ACCOUNT_PROFIT_RATIO,
      max_profit_ratio - this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP,
      (has_super_profited() ? 0.5 : 0.0) * overall_max_profit_ratio,
  };

  const double stop_loss_profit_ratio = stop_loss_profit_ratios.max();

  const double stop_loss_profit =
      this->account_balance.original_balance * stop_loss_profit_ratio;

  return {
      .current_profit = current_profit,
      .max_profit = max_profit,
      .overall_max_profit = overall_max_profit,
      .stop_loss_profit = stop_loss_profit,
      .target_account_profit = target_profit_cash,
      .target_max_profit = target_max_profit,
  };
}

#endif

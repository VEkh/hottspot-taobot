#ifndef OANDA__TAO_BOT_build_account_exit_prices
#define OANDA__TAO_BOT_build_account_exit_prices

#include "account_profit_expanding_trailing_stop_ratio.cpp" // account_profit_expanding_trailing_stop_ratio
#include "tao_bot.h"                                        // Oanda::TaoBot

Oanda::TaoBot::account_exit_prices_t
Oanda::TaoBot::build_account_exit_prices() {
  const double current_balance = this->account_balance.balance;
  const double session_max_profit = this->account_balance.session_max_balance -
                                    this->account_balance.original_balance;

  const double overall_max_profit = this->account_balance.overall_max_balance -
                                    this->account_balance.original_balance;

  const double session_original_profit =
      this->account_balance.session_original_balance -
      this->account_balance.original_balance;

  const double session_target_profit_cash =
      (this->account_balance.original_balance *
       this->TARGET_ACCOUNT_PROFIT_RATIO) +
      session_original_profit;

  const double session_target_max_profit =
      (this->account_balance.original_balance *
       (this->TARGET_ACCOUNT_PROFIT_RATIO +
        this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP)) +
      session_original_profit;

  const double target_profit_cash = (this->account_balance.original_balance *
                                     this->TARGET_ACCOUNT_PROFIT_RATIO);

  const double target_max_profit =
      (this->account_balance.original_balance *
       (this->TARGET_ACCOUNT_PROFIT_RATIO +
        this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP));

  const double current_profit =
      current_balance - this->account_balance.original_balance;

  const double max_profit_ratio =
      session_max_profit / this->account_balance.original_balance;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_balance.original_balance;

  const double session_stop_loss =
      this->account_balance.session_original_balance +
      (this->MAX_ACCOUNT_LOSS_RATIO * this->account_balance.original_balance);

  const double trailing_stop_cash =
      this->account_balance.original_balance *
      account_profit_expanding_trailing_stop_ratio(
          this->account_balance.overall_max_balance -
          this->account_balance.original_balance);

  const double overall_stop_profit_loss =
      overall_max_profit - trailing_stop_cash;

  const double session_trailing_stop_cash =
      this->account_balance.original_balance *
      account_profit_expanding_trailing_stop_ratio(
          this->account_balance.session_max_balance -
          this->account_balance.session_original_balance);

  const double session_stop_profit_loss =
      session_max_profit - session_trailing_stop_cash;

  return {
      .current_profit = current_profit,
      .overall_max_profit = overall_max_profit,
      .overall_stop_profit_loss = overall_stop_profit_loss,
      .session_max_profit = session_max_profit,
      .session_stop_loss = session_stop_loss,
      .session_stop_profit_loss = session_stop_profit_loss,
      .session_target_account_profit = session_target_profit_cash,
      .session_target_max_profit = session_target_max_profit,
      .target_account_profit = target_profit_cash,
      .target_max_profit = target_max_profit,
  };
}

#endif

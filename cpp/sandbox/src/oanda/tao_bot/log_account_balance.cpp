#ifndef OANDA__TAO_BOT_log_account_balance
#define OANDA__TAO_BOT_log_account_balance

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "has_super_profited.cpp"        // has_super_profited
#include "lib/formatted.cpp"             // Formatted
#include "lib/utils/time.cpp"            // ::utils::time_
#include "tao_bot.h"                     // Oanda::TaoBot
#include <iostream>                      // std::cout, std::endl
#include <stdio.h>                       // printf

void Oanda::TaoBot::log_account_balance() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const double balance_delta_percentage =
      (exit_prices_.current_profit / this->account_balance.original_balance) *
      100.0;

  const double session_max_balance_delta_percentage =
      (exit_prices_.session_max_profit /
       this->account_balance.original_balance) *
      100.0;

  const double max_loss = this->account_balance.min_balance -
                          this->account_balance.original_balance;

  const double max_loss_percentage =
      (max_loss / this->account_balance.original_balance) * 100.0;

  const double overall_max_balance_delta_percentage =
      (exit_prices_.overall_max_profit /
       this->account_balance.original_balance) *
      100.0;

  const double session_original_profit =
      this->account_balance.session_original_balance -
      this->account_balance.original_balance;

  const double session_original_profit_percentage =
      (session_original_profit / this->account_balance.original_balance) *
      100.0;

  Formatted::Stream log_color = fmt.green;

  if (exit_prices_.current_profit < 0) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("💰 Account Balance\n");
  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Current Balance:                  $%'.5f (%+'.5f) (%+'.2f%%)%s\n",
         this->account_balance.balance, exit_prices_.current_profit,
         balance_delta_percentage,
         this->account_balance.balance ==
                 this->account_balance.session_max_balance
             ? " 🔥"
             : "");

  printf("Max Balance:                      $%'.5f (%+'.5f) (%+'.2f%%) @ %s\n",
         this->account_balance.session_max_balance,
         exit_prices_.session_max_profit, session_max_balance_delta_percentage,
         ::utils::time_::date_string(
             this->account_balance.session_max_balance_timestamp, "%H:%M %Z",
             "America/Chicago")
             .c_str());

  printf("Overall Max Balance:              $%'.5f (%+'.5f) (%+'.2f%%) @ %s\n",
         this->account_balance.overall_max_balance,
         exit_prices_.overall_max_profit, overall_max_balance_delta_percentage,
         ::utils::time_::date_string(
             this->account_balance.overall_max_balance_timestamp, "%H:%M %Z",
             "America/Chicago")
             .c_str());

  printf(
      "Min Balance:                      $%'.5f (%+'.5f) (%+'.2f%%) @ %s\n",
      this->account_balance.min_balance, max_loss, max_loss_percentage,
      ::utils::time_::date_string(this->account_balance.min_balance_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf("Original Balance:                 $%'.5f\n",
         this->account_balance.original_balance);

  printf("Session Original Balance:         $%'.5f (%+'.5f) (%+'.2f%%)\n",
         this->account_balance.session_original_balance,
         session_original_profit, session_original_profit_percentage);

  printf("Margin Buying Power:              $%'.5f\n",
         this->account_balance.margin_buying_power);

  printf("Stop Loss Profit:                 $%'.5f\n",
         exit_prices_.session_stop_profit_loss);

  printf("Session Target Account Profit:    $%'.5f\n",
         exit_prices_.session_target_account_profit);

  printf("Session Target Max Profit:        $%'.5f%s\n",
         exit_prices_.session_target_max_profit,
         exit_prices_.session_max_profit >=
                 exit_prices_.session_target_max_profit
             ? " ✅"
             : "");

  printf("Target Account Profit:            $%'.5f\n",
         exit_prices_.target_account_profit);

  printf("Target Max Profit:                $%'.5f%s%s\n",
         exit_prices_.target_max_profit,
         exit_prices_.overall_max_profit >= exit_prices_.target_max_profit
             ? " ✅"
             : "",
         has_super_profited() ? "🤑" : "");

  std::cout << fmt.reset << std::endl;
}

#endif

#ifndef ALPACA__TAO_BOT_log_account_balance
#define ALPACA__TAO_BOT_log_account_balance

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "has_super_profited.cpp"        // has_super_profited
#include "lib/formatted.cpp"             // Formatted
#include "lib/utils/time.cpp"            // ::utils::time_
#include "tao_bot.h"                     // Alpaca::TaoBot
#include <iostream>                      // std::cout, std::endl
#include <stdio.h>                       // printf

void Alpaca::TaoBot::log_account_balance() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const double balance_delta_percentage =
      (exit_prices_.current_profit / this->account_balance.original_balance) *
      100.0;

  const double max_balance_delta_percentage =
      (exit_prices_.max_profit / this->account_balance.original_balance) *
      100.0;

  const double overall_max_balance_delta_percentage =
      (exit_prices_.overall_max_profit /
       this->account_balance.original_balance) *
      100.0;

  const double max_loss = this->account_balance.min_balance -
                          this->account_balance.original_balance;

  const double max_loss_percentage =
      (max_loss / this->account_balance.original_balance) * 100.0;

  Formatted::Stream log_color = fmt.green;

  if (exit_prices_.current_profit < 0) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("💰 Account Balance\n");
  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Current Balance:       $%'.2f (%+'.2f) (%+'.2f%%)%s\n",
         this->account_balance.balance, exit_prices_.current_profit,
         balance_delta_percentage,
         this->account_balance.balance == this->account_balance.max_balance
             ? " 🔥"
             : "");

  printf(
      "Max Balance:           $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
      this->account_balance.max_balance, exit_prices_.max_profit,
      max_balance_delta_percentage,
      ::utils::time_::date_string(this->account_balance.max_balance_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf("Overall Max Balance:   $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
         this->account_balance.overall_max_balance,
         exit_prices_.overall_max_profit, overall_max_balance_delta_percentage,
         ::utils::time_::date_string(
             this->account_balance.overall_max_balance_timestamp, "%H:%M %Z",
             "America/Chicago")
             .c_str());

  printf(
      "Min Balance:           $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
      this->account_balance.min_balance, max_loss, max_loss_percentage,
      ::utils::time_::date_string(this->account_balance.min_balance_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf("Original Balance:      $%'.2f\n",
         this->account_balance.original_balance);

  printf("Margin Buying Power:   $%'.2f\n",
         this->account_balance.margin_buying_power);

  printf("Stop Loss Profit:      $%'.2f\n", exit_prices_.stop_loss_profit);

  printf("Target Account Profit: $%'.2f\n", exit_prices_.target_account_profit);

  printf("Target Max Profit:     $%'.2f%s%s\n", exit_prices_.target_max_profit,
         exit_prices_.max_profit >= exit_prices_.target_max_profit ? " ✅" : "",
         has_super_profited() ? "🤑" : "");

  std::cout << fmt.reset << std::endl;
}

#endif

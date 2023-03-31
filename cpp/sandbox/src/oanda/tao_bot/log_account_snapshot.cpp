#ifndef OANDA__TAO_BOT_log_account_snapshot
#define OANDA__TAO_BOT_log_account_snapshot

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "has_super_profited.cpp"        // has_super_profited
#include "lib/formatted.cpp"             // Formatted
#include "lib/utils/time.cpp"            // ::utils::time_
#include "tao_bot.h"                     // Oanda::TaoBot
#include <iostream>                      // std::cout, std::endl
#include <stdio.h>                       // printf

void Oanda::TaoBot::log_account_snapshot() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const double equity_delta_percentage =
      (exit_prices_.current_profit / this->account_snapshot.original_equity) *
      100.0;

  const double session_max_equity_delta_percentage =
      (exit_prices_.session_max_profit /
       this->account_snapshot.original_equity) *
      100.0;

  const double max_loss = this->account_snapshot.min_equity -
                          this->account_snapshot.original_equity;

  const double max_loss_percentage =
      (max_loss / this->account_snapshot.original_equity) * 100.0;

  const double max_equity_delta_percentage =
      (exit_prices_.overall_max_profit /
       this->account_snapshot.original_equity) *
      100.0;

  const double session_original_profit =
      this->account_snapshot.session_original_equity -
      this->account_snapshot.original_equity;

  const double session_original_profit_percentage =
      (session_original_profit / this->account_snapshot.original_equity) *
      100.0;

  Formatted::Stream log_color = fmt.green;

  if (exit_prices_.current_profit < 0) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("💰 Account Equity\n");
  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Current Equity:                   $%'.5f (%+'.5f) (%+'.2f%%)%s\n",
         this->account_snapshot.equity, exit_prices_.current_profit,
         equity_delta_percentage,
         this->account_snapshot.equity ==
                 this->account_snapshot.session_max_equity
             ? " 🔥"
             : "");

  printf("Max Equity:                       $%'.5f (%+'.5f) (%+'.2f%%) @ %s\n",
         this->account_snapshot.session_max_equity,
         exit_prices_.session_max_profit, session_max_equity_delta_percentage,
         ::utils::time_::date_string(
             this->account_snapshot.session_max_equity_timestamp, "%H:%M %Z",
             "America/Chicago")
             .c_str());

  printf(
      "Overall Max Equity:               $%'.5f (%+'.5f) (%+'.2f%%) @ %s\n",
      this->account_snapshot.max_equity, exit_prices_.overall_max_profit,
      max_equity_delta_percentage,
      ::utils::time_::date_string(this->account_snapshot.max_equity_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf(
      "Min Equity:                       $%'.5f (%+'.5f) (%+'.2f%%) @ %s\n",
      this->account_snapshot.min_equity, max_loss, max_loss_percentage,
      ::utils::time_::date_string(this->account_snapshot.min_equity_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf("Original Equity:                  $%'.5f\n",
         this->account_snapshot.original_equity);

  printf("Session Original Equity:          $%'.5f (%+'.5f) (%+'.2f%%)\n",
         this->account_snapshot.session_original_equity,
         session_original_profit, session_original_profit_percentage);

  printf("Margin Buying Power:              $%'.5f\n",
         this->account_snapshot.margin_buying_power);

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

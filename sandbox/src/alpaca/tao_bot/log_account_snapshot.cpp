#ifndef ALPACA__TAO_BOT_log_account_snapshot
#define ALPACA__TAO_BOT_log_account_snapshot

#include "build_account_exit_prices.cpp"   // build_account_exit_prices
#include "has_super_profited.cpp"          // has_super_profited
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/time.cpp"              // ::utils::time_
#include "tao_bot.h"                       // Alpaca::TaoBot
#include "target_account_profit_ratio.cpp" // target_account_profit_ratio
#include <iostream>                        // std::cout, std::endl
#include <stdio.h>                         // printf

void Alpaca::TaoBot::log_account_snapshot() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const double equity_delta_percentage =
      (exit_prices_.current_profit / this->account_snapshot.original_equity) *
      100.0;

  const double min_profit = this->account_snapshot.min_equity -
                            this->account_snapshot.original_equity;

  const double min_profit_percentage =
      (min_profit / this->account_snapshot.original_equity) * 100.0;

  const double max_equity_delta_percentage =
      (exit_prices_.max_profit / this->account_snapshot.original_equity) *
      100.0;

  Formatted::Stream log_color = fmt.green;

  if (exit_prices_.current_profit < 0) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("💰 Account Snapshot\n");
  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Current Equity:                   $%'.2f (%+'.2f) (%+'.2f%%)%s\n",
         this->account_snapshot.equity, exit_prices_.current_profit,
         equity_delta_percentage,
         this->account_snapshot.equity == this->account_snapshot.max_equity
             ? " 🔥"
             : "");

  printf(
      "Max Equity:                       $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
      this->account_snapshot.max_equity, exit_prices_.max_profit,
      max_equity_delta_percentage,
      ::utils::time_::date_string(this->account_snapshot.max_equity_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf(
      "Min Equity:                       $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
      this->account_snapshot.min_equity, min_profit, min_profit_percentage,
      ::utils::time_::date_string(this->account_snapshot.min_equity_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf("Original Equity:                  $%'.2f\n",
         this->account_snapshot.original_equity);

  printf("Margin Buying Power:              $%'.2f\n",
         this->account_snapshot.margin_buying_power);

  if (target_account_profit_ratio()) {
    printf("Stop Loss Profit:                 $%'.2f\n",
           exit_prices_.stop_profit_loss);

    printf("Target Account Profit:            $%'.2f\n",
           exit_prices_.target_account_profit);

    printf("Target Max Profit:                $%'.2f%s%s\n",
           exit_prices_.target_max_profit,
           exit_prices_.max_profit >= exit_prices_.target_max_profit ? " ✅"
                                                                     : "",
           has_super_profited() ? "🤑" : "");
  }

  std::cout << fmt.reset << std::endl;
}

#endif

#ifndef OANDA__TAO_BOT_log_account_snapshot
#define OANDA__TAO_BOT_log_account_snapshot

#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Oanda::TaoBot
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf

void Oanda::TaoBot::log_account_snapshot() {
  const double current_equity = this->account_snapshot.equity;

  const double current_profit =
      current_equity - this->account_snapshot.original_equity;

  const double max_profit = this->account_snapshot.max_equity -
                            this->account_snapshot.original_equity;

  const double min_profit = this->account_snapshot.min_equity -
                            this->account_snapshot.original_equity;

  const double equity_delta_percentage =
      (current_profit / this->account_snapshot.original_equity) * 100.0;

  const double min_profit_percentage =
      (min_profit / this->account_snapshot.original_equity) * 100.0;

  const double max_profit_percentage =
      (max_profit / this->account_snapshot.original_equity) * 100.0;

  Formatted::Stream log_color = fmt.green;

  if (current_profit < 0) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("💰 Account Snapshot\n");
  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Current Equity:                   $%'.5f (%+'.5f) (%+'.2f%%)%s\n",
         this->account_snapshot.equity, current_profit, equity_delta_percentage,
         this->account_snapshot.equity == this->account_snapshot.max_equity
             ? " 🔥"
             : "");

  printf(
      "Max Equity:                       $%'.5f (%+'.5f) (%+'.2f%%) @ %s\n",
      this->account_snapshot.max_equity, max_profit, max_profit_percentage,
      ::utils::time_::date_string(this->account_snapshot.max_equity_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf(
      "Min Equity:                       $%'.5f (%+'.5f) (%+'.2f%%) @ %s\n",
      this->account_snapshot.min_equity, min_profit, min_profit_percentage,
      ::utils::time_::date_string(this->account_snapshot.min_equity_timestamp,
                                  "%H:%M %Z", "America/Chicago")
          .c_str());

  printf("Original Equity:                  $%'.5f\n",
         this->account_snapshot.original_equity);

  printf("Margin Buying Power:              $%'.5f\n",
         this->account_snapshot.margin_buying_power);

  std::cout << fmt.reset << std::endl;
}

#endif

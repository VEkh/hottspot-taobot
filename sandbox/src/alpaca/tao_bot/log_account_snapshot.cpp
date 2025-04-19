#ifndef ALPACA__TAO_BOT_log_account_snapshot
#define ALPACA__TAO_BOT_log_account_snapshot

#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf

void Alpaca::TaoBot::log_account_snapshot() {
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

  printf("Current Equity:                   $%'.2f (%+'.2f) (%+'.2f%%)%s\n",
         this->account_snapshot.equity, current_profit, equity_delta_percentage,
         this->account_snapshot.equity == this->account_snapshot.max_equity
             ? " 🔥"
             : "");

  printf(
      "Max Equity:                       $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
      this->account_snapshot.max_equity, max_profit, max_profit_percentage,
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

  const double account_stop_loss_ratio =
      this->api_client.config.account_stop_loss_ratio;

  if (account_stop_loss_ratio) {
    const double stop_loss_equity =
        this->account_snapshot.original_equity * (1 + account_stop_loss_ratio);

    printf("Stop Loss Equity:                 $%'.2f (%.2f%%)\n",
           stop_loss_equity, 100.0 * account_stop_loss_ratio);
  }

  printf("Margin Buying Power:              $%'.2f\n",
         this->account_snapshot.margin_buying_power);

  std::cout << fmt.reset << std::endl;
}

#endif

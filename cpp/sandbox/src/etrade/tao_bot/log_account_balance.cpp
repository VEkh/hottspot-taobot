#ifndef ETRADE__TAO_BOT_log_account_balance
#define ETRADE__TAO_BOT_log_account_balance

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // ETrade::TaoBot
#include <iostream>          // std::cout, std::endl
#include <stdio.h>           // printf

void ETrade::TaoBot::log_account_balance() {
  const double balance_delta =
      this->account_balance.balance - this->account_snapshot.original_balance;

  const double balance_delta_percentage =
      (balance_delta / this->account_snapshot.original_balance) * 100.0;

  Formatted::Stream log_color = fmt.green;

  if (this->account_snapshot.balance < this->account_snapshot.original_balance) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("💰 Account Balance\n");
  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Current Balance:     $%'.2f (%+'.2f) (%+'.2f%%)\n",
         this->account_snapshot.balance, balance_delta,
         balance_delta_percentage);

  printf("Original Balance:    $%'.2f\n",
         this->account_snapshot.original_balance);

  printf("Margin Buying Power: $%'.2f\n",
         this->account_snapshot.margin_buying_power);

  std::cout << fmt.reset << std::endl;
}

#endif

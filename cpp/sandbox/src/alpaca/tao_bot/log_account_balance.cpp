#ifndef ALPACA__TAO_BOT_log_account_balance
#define ALPACA__TAO_BOT_log_account_balance

#include "lib/formatted.cpp" // Formatted
#include "tao_bot.h"         // Alpaca::TaoBot
#include <iostream>          // std::cout, std::endl
#include <stdio.h>           // printf

void Alpaca::TaoBot::log_account_balance() {
  const double balance_delta =
      this->account_balance.balance - this->original_account_balance.balance;

  const double balance_delta_percentage =
      (balance_delta / this->original_account_balance.balance) * 100.0;

  Formatted::Stream log_color = fmt.green;

  if (this->account_balance.balance < this->original_account_balance.balance) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("💰 Account Balance\n");
  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Current Balance:     $%'.2f (%+'.2f) (%+'.2f%%)\n",
         this->account_balance.balance, balance_delta,
         balance_delta_percentage);

  printf("Original Balance:    $%'.2f\n",
         this->original_account_balance.balance);

  printf("Margin Buying Power: $%'.2f\n",
         this->account_balance.margin_buying_power);

  std::cout << fmt.reset << std::endl;
}

#endif

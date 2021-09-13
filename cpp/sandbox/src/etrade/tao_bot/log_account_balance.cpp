#ifndef ETRADE__TAO_BOT_log_account_balance
#define ETRADE__TAO_BOT_log_account_balance

/*
 * ETrade::TaoBot
 * fmt
 */
#include "tao_bot.h"

#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/float.cpp"   // utils::float_
#include "lib/utils/integer.cpp" // utils::integer_
#include <iomanip>               // std::setprecision
#include <iostream>              // std::cout, std::endl, std::fixed
#include <stdio.h>               // printf

void ETrade::TaoBot::log_account_balance() {
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
         this->account_balance.day_trading_margin_buying_power);

  std::cout << fmt.reset << std::endl;
}

#endif

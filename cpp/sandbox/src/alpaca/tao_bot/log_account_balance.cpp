#ifndef ALPACA__TAO_BOT_log_account_balance
#define ALPACA__TAO_BOT_log_account_balance

#include "lib/formatted.cpp"       // Formatted
#include "tao_bot.h"               // Alpaca::TaoBot
#include "target_daily_profit.cpp" // target_daily_profit
#include <iostream>                // std::cout, std::endl
#include <stdio.h>                 // printf

void Alpaca::TaoBot::log_account_balance(
    account_balance_t account_balance_,
    account_balance_t original_account_balance_, const char *label) {
  const double balance_delta =
      account_balance_.balance - original_account_balance_.balance;

  const double balance_delta_percentage =
      (balance_delta / original_account_balance_.balance) * 100.0;

  Formatted::Stream log_color = fmt.green;

  if (account_balance_.balance < original_account_balance_.balance) {
    log_color = fmt.red;
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("💰 %s\n", label);
  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Current Balance:     $%'.2f (%+'.2f) (%+'.2f%%)\n",
         account_balance_.balance, balance_delta, balance_delta_percentage);

  printf("Original Balance:    $%'.2f\n", original_account_balance_.balance);
  printf("Margin Buying Power: $%'.2f\n", account_balance_.margin_buying_power);
  printf("Target Asset Max Profit: $%'.2f\n",
         target_daily_profit() / (1 - this->TARGET_DAILY_PROFIT_TRAILING_STOP));
  printf("Target Asset Profit: $%'.2f\n", target_daily_profit());

  std::cout << fmt.reset << std::endl;
}

#endif

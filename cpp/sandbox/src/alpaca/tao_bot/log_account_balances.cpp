#ifndef ALPACA__TAO_BOT_log_account_balances
#define ALPACA__TAO_BOT_log_account_balances

#include "log_account_balance.cpp" // log_account_balance
#include "tao_bot.h"               // Alpaca::TaoBot
#include <algorithm>               // std::min
#include <iostream>                // std::cout, std::endl
#include <stdio.h>                 // printf

void Alpaca::TaoBot::log_account_balances() {
  log_account_balance(this->account_balance, this->original_account_balance,
                      "Account Balance");

  if (is_hedging()) {
    const account_balance_t total_accounts_balance = {
        .balance =
            this->account_balance.balance + this->hedge_account_balance.balance,
        .margin_buying_power = this->account_balance.margin_buying_power +
                               this->hedge_account_balance.margin_buying_power,
        .margin_multiplier =
            std::min(this->account_balance.margin_multiplier,
                     this->hedge_account_balance.margin_multiplier),
    };

    const account_balance_t total_original_accounts_balance = {
        .balance = this->original_account_balance.balance +
                   this->original_hedge_account_balance.balance,
        .margin_buying_power =
            this->original_account_balance.margin_buying_power +
            this->original_hedge_account_balance.margin_buying_power,
        .margin_multiplier =
            std::min(this->original_account_balance.margin_multiplier,
                     this->original_hedge_account_balance.margin_multiplier),
    };

    log_account_balance(this->hedge_account_balance,
                        this->original_hedge_account_balance,
                        "Hedge Account Balance");

    log_account_balance(total_accounts_balance, total_original_accounts_balance,
                        "Total Accounts Balance");
  }
}

#endif

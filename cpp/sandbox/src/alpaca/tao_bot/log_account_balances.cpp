#ifndef ALPACA__TAO_BOT_log_account_balances
#define ALPACA__TAO_BOT_log_account_balances

#include "log_account_balance.cpp" // log_account_balance
#include "tao_bot.h"               // Alpaca::TaoBot

void Alpaca::TaoBot::log_account_balances() {
  log_account_balance(this->account_balance, this->original_account_balance,
                      "Account Balance");
}

#endif

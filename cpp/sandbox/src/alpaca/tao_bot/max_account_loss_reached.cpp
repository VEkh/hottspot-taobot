#ifndef ALPACA__TAO_BOT_max_account_loss_reached
#define ALPACA__TAO_BOT_max_account_loss_reached

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Alpaca::TaoBot

bool Alpaca::TaoBot::max_account_loss_reached() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  return this->account_balance.min_balance <= exit_prices_.session_stop_loss &&
         this->account_balance.balance > exit_prices_.session_stop_loss;
}

#endif

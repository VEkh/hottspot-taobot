#ifndef OANDA__TAO_BOT_max_account_loss_reached
#define OANDA__TAO_BOT_max_account_loss_reached

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Oanda::TaoBot

bool Oanda::TaoBot::max_account_loss_reached() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  return this->account_balance.balance <= exit_prices_.session_stop_loss;
}

#endif

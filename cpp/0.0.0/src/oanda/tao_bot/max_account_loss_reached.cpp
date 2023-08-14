#ifndef OANDA__TAO_BOT_max_account_loss_reached
#define OANDA__TAO_BOT_max_account_loss_reached

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Oanda::TaoBot

bool Oanda::TaoBot::max_account_loss_reached() {
  return false;

  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  return (exit_prices_.current_profit /
          this->account_snapshot.original_equity) <=
         this->MAX_ACCOUNT_LOSS_RATIO;
}

#endif

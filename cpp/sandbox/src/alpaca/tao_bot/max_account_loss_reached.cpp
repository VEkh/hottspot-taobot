#ifndef ALPACA__TAO_BOT_max_account_loss_reached
#define ALPACA__TAO_BOT_max_account_loss_reached

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Alpaca::TaoBot

bool Alpaca::TaoBot::max_account_loss_reached() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  return (exit_prices_.current_profit /
          this->account_balance.original_balance) <=
         this->MAX_ACCOUNT_LOSS_RATIO;
}

#endif

#ifndef ALPACA__TAO_BOT_max_account_loss_reached
#define ALPACA__TAO_BOT_max_account_loss_reached

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Alpaca::TaoBot

bool Alpaca::TaoBot::max_account_loss_reached() {
  if (!this->api_client.is_live()) {
    return false;
  }

  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const double current_profit_ratio =
      exit_prices_.current_profit / this->account_balance.original_balance;

  return current_profit_ratio <= this->MAX_ACCOUNT_LOSS_RATIO;
}

#endif

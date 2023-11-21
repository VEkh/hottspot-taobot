#ifndef ALPACA__TAO_BOT_max_account_loss_reached
#define ALPACA__TAO_BOT_max_account_loss_reached

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Alpaca::TaoBot

bool Alpaca::TaoBot::max_account_loss_reached() {
  const double loss_ratio = this->api_client.config.account_stop_loss_ratio;

  if (!loss_ratio) {
    return false;
  }

  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const double current_stop_loss_ratio =
      (this->account_snapshot.min_equity -
       this->account_snapshot.original_equity) /
      this->account_snapshot.original_equity;

  return current_stop_loss_ratio <= loss_ratio;
}

#endif

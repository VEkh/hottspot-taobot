#ifndef ALPACA__TAO_BOT_max_account_loss_reached
#define ALPACA__TAO_BOT_max_account_loss_reached

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::max_account_loss_reached() {
  return false;

  const double loss_ratio =
      (this->account_balance.balance - this->original_account_balance.balance) /
      this->original_account_balance.balance;

  return loss_ratio <= -this->MAX_ACCOUNT_LOSS_RATIO;
}

#endif

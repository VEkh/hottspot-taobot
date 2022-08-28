#ifndef OANDA__TAO_BOT_max_account_loss_reached
#define OANDA__TAO_BOT_max_account_loss_reached

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::max_account_loss_reached() {
  const double loss_ratio =
      (this->account_balance.balance - this->account_balance.original_balance) /
      this->account_balance.original_balance;

  return loss_ratio <= -this->MAX_ACCOUNT_LOSS_RATIO;
}

#endif

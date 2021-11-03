#ifndef ETRADE__TAO_BOT_loss_to_recover
#define ETRADE__TAO_BOT_loss_to_recover

#include "tao_bot.h" // ETrade::TaoBot

double ETrade::TaoBot::loss_to_recover() {
  const double total_deficit =
      this->performance.current_balance - this->performance.max_balance;

  return this->performance.current_loss_streak_balance;
}

#endif

#ifndef ETRADE__TAO_BOT_loss_to_recover
#define ETRADE__TAO_BOT_loss_to_recover

#include "tao_bot.h" // ETrade::TaoBot
#include <algorithm> // std::min

double ETrade::TaoBot::loss_to_recover() {
  const double current_loss_streak_balance =
      this->performance.current_loss_streak_balance;

  const double total_deficit =
      this->performance.current_balance - this->performance.max_balance;

  if (current_loss_streak_balance) {
    return current_loss_streak_balance;
  }

  if (total_deficit) {
    const double borrowed_deficit = 50;
    return std::min(total_deficit, borrowed_deficit);
  }

  return 0;
}

#endif

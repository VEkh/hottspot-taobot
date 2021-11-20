#ifndef ETRADE__TAO_BOT_loss_to_recover
#define ETRADE__TAO_BOT_loss_to_recover

#include "tao_bot.h" // ETrade::TaoBot
#include <algorithm> // std::min
#include <math.h>    // abs

double ETrade::TaoBot::loss_to_recover() {
  const double current_loss_streak_balance =
      this->performance.current_loss_streak_balance;

  return current_loss_streak_balance;
}
}

#endif

#ifndef OANDA__TAO_BOT_get_loss_leader
#define OANDA__TAO_BOT_get_loss_leader

#include "tao_bot.h" // Oanda::TaoBot, performance_t
#include <string>    // std::string

Oanda::TaoBot::performance_t
Oanda::TaoBot::get_loss_leader(std::list<performance_t> &performances) {
  performance_t loss_leader;
  double min_deficit = 0.00;

  std::list<performance_t>::iterator it;

  for (it = performances.begin(); it != performances.end(); it++) {
    const double deficit = it->current_loss_streak_balance;

    if (deficit < min_deficit) {
      min_deficit = deficit;
      loss_leader = *it;
    }
  }

  return loss_leader;
}

#endif

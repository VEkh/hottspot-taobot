#ifndef ETRADE__TAO_BOT_get_loss_leader
#define ETRADE__TAO_BOT_get_loss_leader

#include "tao_bot.h" // ETrade::TaoBot
#include <string>    // std::string

ETrade::TaoBot::performance_t
ETrade::TaoBot::get_loss_leader(std::list<performance_t> &performances) {
  performance_t loss_leader;
  double min_deficit = 0.00;

  std::list<performance_t>::iterator it;

  for (it = performances.begin(); it != performances.end(); it++) {
    const double deficit = it->current_balance - it->max_balance;

    if (deficit < min_deficit) {
      min_deficit = deficit;
      loss_leader = *it;
    }
  }

  return loss_leader;
}

#endif

#ifndef ETRADE__TAO_BOT_loss_to_recover
#define ETRADE__TAO_BOT_loss_to_recover

/*
 * ETrade::TaoBot
 * performance_t
 */
#include "tao_bot.h"

double ETrade::TaoBot::loss_to_recover() {
  return this->performance.current_balance - this->performance.max_balance;
}

#endif

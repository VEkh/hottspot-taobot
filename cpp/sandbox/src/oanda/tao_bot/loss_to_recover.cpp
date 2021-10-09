#ifndef OANDA__TAO_BOT_loss_to_recover
#define OANDA__TAO_BOT_loss_to_recover

/*
 * Oanda::TaoBot
 * performance_t
 */
#include "tao_bot.h"

#include "build_performance.cpp" // build_performance

double Oanda::TaoBot::loss_to_recover() {
  return this->performance.current_balance - this->performance.max_balance;
}

#endif

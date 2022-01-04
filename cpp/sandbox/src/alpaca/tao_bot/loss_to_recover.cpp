#ifndef ALPACA__TAO_BOT_loss_to_recover
#define ALPACA__TAO_BOT_loss_to_recover

#include "tao_bot.h" // Alpaca::TaoBot

double Alpaca::TaoBot::loss_to_recover() {
  return this->performance.current_loss_streak_balance;
}

#endif

#ifndef OANDA__TAO_BOT_target_account_profit
#define OANDA__TAO_BOT_target_account_profit

#include "tao_bot.h" // Oanda::TaoBot

double Oanda::TaoBot::target_account_profit(const double return_ratio) {
  return this->account_balance.original_balance * return_ratio;
}

#endif

#ifndef OANDA__TAO_BOT_target_daily_profit
#define OANDA__TAO_BOT_target_daily_profit

#include "tao_bot.h" // Oanda::TaoBot

double Oanda::TaoBot::target_daily_profit(const double return_ratio) {
  const double original_account_balance =
      this->original_account_balance.balance;

  return original_account_balance * return_ratio;
}

#endif

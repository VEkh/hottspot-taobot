#ifndef OANDA__TAO_BOT_target_daily_profit
#define OANDA__TAO_BOT_target_daily_profit

#include "tao_bot.h" // Oanda::TaoBot

double Oanda::TaoBot::target_daily_profit(const double return_ratio) {
  return this->account_balance.original_balance * return_ratio;
}

#endif

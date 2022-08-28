#ifndef ALPACA__TAO_BOT_target_daily_profit
#define ALPACA__TAO_BOT_target_daily_profit

#include "tao_bot.h" // Alpaca::TaoBot

double Alpaca::TaoBot::target_daily_profit(const double return_ratio) {
  return this->account_balance.original_balance * return_ratio;
}

#endif

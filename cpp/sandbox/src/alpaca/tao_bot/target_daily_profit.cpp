#ifndef ALPACA__TAO_BOT_target_daily_profit
#define ALPACA__TAO_BOT_target_daily_profit

#include "tao_bot.h"                   // Alpaca::TaoBot
#include "tradeable_symbols_count.cpp" // tradeable_symbols_count

double Alpaca::TaoBot::target_daily_profit() {
  const double original_account_balance =
      this->original_account_balance.balance;

  return (original_account_balance * this->TARGET_DAILY_PROFIT) *
         (1.0 / tradeable_symbols_count());
}

#endif

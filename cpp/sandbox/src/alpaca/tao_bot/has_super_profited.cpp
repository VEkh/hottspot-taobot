#ifndef ALPACA__TAO_BOT_has_super_profited
#define ALPACA__TAO_BOT_has_super_profited

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

bool Alpaca::TaoBot::has_super_profited() {
  const double overall_max_profit = this->account_balance.overall_max_balance -
                                    this->account_balance.original_balance;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_balance.original_balance;

  double super_profit_ratio = this->TARGET_ACCOUNT_PROFIT_RATIO;

  return overall_max_profit_ratio >= super_profit_ratio;
}

#endif

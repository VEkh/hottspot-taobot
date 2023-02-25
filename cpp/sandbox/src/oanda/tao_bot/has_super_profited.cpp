#ifndef OANDA__TAO_BOT_has_super_profited
#define OANDA__TAO_BOT_has_super_profited

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Oanda::TaoBot

bool Oanda::TaoBot::has_super_profited() {
  const double overall_max_profit = this->account_balance.overall_max_balance -
                                    this->account_balance.original_balance;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_balance.original_balance;

  double super_profit_ratio = this->TARGET_ACCOUNT_PROFIT_RATIO / (2.0 / 3);

  return overall_max_profit_ratio >= super_profit_ratio;
}

#endif

#ifndef OANDA__TAO_BOT_has_super_profited
#define OANDA__TAO_BOT_has_super_profited

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Oanda::TaoBot

bool Oanda::TaoBot::has_super_profited() {
  const double overall_max_profit =
      this->account_snapshot.max_equity - this->account_snapshot.original_equity;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_snapshot.original_equity;

  double super_profit_ratio = this->TARGET_ACCOUNT_PROFIT_RATIO / (2.0 / 3);

  return overall_max_profit_ratio >= super_profit_ratio;
}

#endif

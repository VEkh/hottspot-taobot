#ifndef ALPACA__TAO_BOT_has_super_profited
#define ALPACA__TAO_BOT_has_super_profited

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

bool Alpaca::TaoBot::has_super_profited() {
  const double overall_max_profit =
      this->account_snapshot.max_equity - this->account_snapshot.original_equity;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_snapshot.original_equity;

  double super_profit_ratio = this->TARGET_ACCOUNT_PROFIT_RATIO;

  return overall_max_profit_ratio >= super_profit_ratio;
}

#endif

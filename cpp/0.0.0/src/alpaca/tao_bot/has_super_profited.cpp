#ifndef ALPACA__TAO_BOT_has_super_profited
#define ALPACA__TAO_BOT_has_super_profited

#include "lib/utils/time.cpp"              // ::utils::time_
#include "tao_bot.h"                       // Alpaca::TaoBot
#include "target_account_profit_ratio.cpp" // target_account_profit_ratio

bool Alpaca::TaoBot::has_super_profited() {
  const double max_profit = this->account_snapshot.max_equity -
                            this->account_snapshot.original_equity;

  const double max_profit_ratio =
      max_profit / this->account_snapshot.original_equity;

  double super_profit_ratio = target_account_profit_ratio();

  return max_profit_ratio >= super_profit_ratio;
}

#endif

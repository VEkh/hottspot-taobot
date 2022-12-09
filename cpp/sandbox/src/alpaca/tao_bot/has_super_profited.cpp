#ifndef ALPACA__TAO_BOT_has_super_profited
#define ALPACA__TAO_BOT_has_super_profited

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

bool Alpaca::TaoBot::has_super_profited() {
  const double overall_max_profit = this->account_balance.overall_max_balance -
                                    this->account_balance.original_balance;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_balance.original_balance;

  double super_profit_ratio = 0.04;

  if (::utils::time_::is_at_least({9, 30}, "America/Chicago")) {
    super_profit_ratio = 0.02;
  } else if (::utils::time_::is_at_least({9, 0}, "America/Chicago")) {
    super_profit_ratio = 0.03;
  }

  return overall_max_profit_ratio >= super_profit_ratio;
}

#endif

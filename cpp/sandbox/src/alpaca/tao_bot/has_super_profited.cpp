#ifndef ALPACA__TAO_BOT_has_super_profited
#define ALPACA__TAO_BOT_has_super_profited

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

bool Alpaca::TaoBot::has_super_profited() {
  const double overall_max_profit = this->account_balance.overall_max_balance -
                                    this->account_balance.original_balance;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_balance.original_balance;

  double super_profit_ratio = 0.015;

  if (::utils::time_::is_at_least({8, 50}, "America/Chicago")) {
    super_profit_ratio = 0.005;
  } else if (::utils::time_::is_at_least({8, 40}, "America/Chicago")) {
    super_profit_ratio = 0.01;
  }

  return overall_max_profit_ratio >= super_profit_ratio;
}

#endif

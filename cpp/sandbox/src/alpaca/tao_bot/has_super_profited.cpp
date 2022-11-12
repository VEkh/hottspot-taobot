#ifndef ALPACA__TAO_BOT_has_super_profited
#define ALPACA__TAO_BOT_has_super_profited

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::has_super_profited() {
  const double overall_max_profit = this->account_balance.overall_max_balance -
                                    this->account_balance.original_balance;

  const double overall_max_profit_ratio =
      overall_max_profit / this->account_balance.original_balance;

  const double super_profit_raito =
      2 * this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP;

  return overall_max_profit_ratio >= super_profit_raito;
}

#endif

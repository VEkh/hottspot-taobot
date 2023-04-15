#ifndef ALPACA__TAO_BOT_target_account_profit
#define ALPACA__TAO_BOT_target_account_profit

// NOTE: Deprecated

#include "lib/utils/float.cpp" // ::utils::float_
#include "tao_bot.h"           // Alpaca::TaoBot
#include <algorithm>           // std::max

double Alpaca::TaoBot::target_account_profit() {
  const double min_target = 0.0105;
  const double one_hour_seconds = 60 * 60;

  const double session_max_profit_ratio =
      (this->account_snapshot.session_max_equity /
       this->account_snapshot.original_equity) -
      1;

  const double max_target =
      std::max(session_max_profit_ratio, min_target) + 0.03;

  const double max_equity_duration =
      (this->current_epoch -
       this->account_snapshot.session_max_equity_timestamp) /
      one_hour_seconds;

  return ::utils::float_::sigmoid(max_target, min_target, max_equity_duration,
                                  -6.5, 0.25);
}

#endif

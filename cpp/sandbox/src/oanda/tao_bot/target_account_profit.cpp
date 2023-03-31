#ifndef OANDA__TAO_BOT_target_account_profit
#define OANDA__TAO_BOT_target_account_profit

#include "lib/utils/float.cpp" // ::utils::float_
#include "tao_bot.h"           // Oanda::TaoBot
#include <algorithm>           // std::max
#include <ctime>               // std::time

double Oanda::TaoBot::target_account_profit() {
  const double min_target = 0.0105;
  const double one_hour_seconds = 60 * 60;

  const double max_profit_ratio = (this->account_snapshot.max_equity /
                                   this->account_snapshot.original_equity) -
                                  1;

  const double max_target = std::max(max_profit_ratio, min_target) + 0.02;

  const double max_equity_duration =
      (std::time(nullptr) - this->account_snapshot.max_equity_timestamp) /
      one_hour_seconds;

  return ::utils::float_::sigmoid(max_target, min_target, max_equity_duration,
                                  -6.5, 0.25);
}

#endif

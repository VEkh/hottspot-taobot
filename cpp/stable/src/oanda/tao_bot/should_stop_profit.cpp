#ifndef OANDA__TAO_BOT_should_stop_profit
#define OANDA__TAO_BOT_should_stop_profit

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Oanda::TaoBot, account_exit_prices_t

bool Oanda::TaoBot::should_stop_profit() {
  return false;

  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const bool is_profit_slipping =
      exit_prices_.max_profit >= exit_prices_.target_max_profit &&
      exit_prices_.current_profit <= exit_prices_.stop_profit_loss;

  return is_profit_slipping;
}

#endif

#ifndef ALPACA__TAO_BOT_should_stop_profit
#define ALPACA__TAO_BOT_should_stop_profit

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h" // Alpaca::TaoBot, account_exit_prices_t
#include "target_account_profit_ratio.cpp" // target_account_profit_ratio

bool Alpaca::TaoBot::should_stop_profit() {
  if (!target_account_profit_ratio()) {
    return false;
  }

  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  return exit_prices_.max_profit >= exit_prices_.target_max_profit;
}

#endif

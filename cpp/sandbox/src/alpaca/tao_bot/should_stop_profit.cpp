#ifndef ALPACA__TAO_BOT_should_stop_profit
#define ALPACA__TAO_BOT_should_stop_profit

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "has_super_profited.cpp"        // has_super_profited
#include "tao_bot.h" // Alpaca::TaoBot, account_exit_prices_t

bool Alpaca::TaoBot::should_stop_profit() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();
  const double attained_max_profit = has_super_profited()
                                         ? exit_prices_.overall_max_profit
                                         : exit_prices_.max_profit;

  return attained_max_profit >= exit_prices_.target_max_profit &&
         exit_prices_.current_profit < exit_prices_.stop_loss_profit &&
         exit_prices_.current_profit >= exit_prices_.target_account_profit;
}

#endif

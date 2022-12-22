#ifndef ALPACA__TAO_BOT_should_stop_profit
#define ALPACA__TAO_BOT_should_stop_profit

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "has_super_profited.cpp"        // has_super_profited
#include "tao_bot.h" // Alpaca::TaoBot, account_exit_prices_t

bool Alpaca::TaoBot::should_stop_profit() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const bool is_session_profit_slipping =
      exit_prices_.max_profit >= exit_prices_.target_max_profit &&
      exit_prices_.current_profit <= exit_prices_.session_stop_profit_loss;

  if (has_super_profited() && !is_session_profit_slipping) {
    const double target_profit_cash = this->account_balance.original_balance *
                                      this->TARGET_ACCOUNT_PROFIT_RATIO;

    return exit_prices_.current_profit > target_profit_cash &&
           exit_prices_.current_profit <=
               (2.0 / 3) * exit_prices_.overall_max_profit;
  }

  return is_session_profit_slipping;
}

#endif

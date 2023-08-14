#ifndef ALPACA__TAO_BOT_should_stop_profit
#define ALPACA__TAO_BOT_should_stop_profit

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h" // Alpaca::TaoBot, account_exit_prices_t

#include <regex> // std::regex, std::regex_search

bool Alpaca::TaoBot::should_stop_profit() {
  if (!this->backtest.is_active &&
      this->api_client.config.api_key == "paper-alpha") {
    return false;
  }

  if (this->backtest.is_active &&
      !std::regex_search(this->backtest.config.api_key_id,
                         std::regex("-act_(.+)__(.+)$"))) {
    return false;
  }

  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const bool is_profit_slipping =
      exit_prices_.max_profit >= exit_prices_.target_max_profit &&
      exit_prices_.current_profit <= exit_prices_.stop_profit_loss;

  const double init_profit =
      this->session_init_account_snapshot.equity -
      this->session_init_account_snapshot.original_equity;

  if (init_profit >= exit_prices_.target_max_profit) {
    return true;
  }

  if (this->has_target_profit_slipped) {
    return exit_prices_.current_profit >= exit_prices_.target_max_profit;
  }

  if (is_profit_slipping) {
    this->has_target_profit_slipped = true;

    return true;
  }

  return false;
}

#endif

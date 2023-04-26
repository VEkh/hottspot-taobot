#ifndef ALPACA__TAO_BOT_should_stop_profit
#define ALPACA__TAO_BOT_should_stop_profit

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h" // Alpaca::TaoBot, account_exit_prices_t

#include <regex> // std::regex, std::regex_search

bool Alpaca::TaoBot::should_stop_profit() {
  if (!this->backtest.is_active &&
      this->api_client.config.api_key != "paper-beta") {
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

  return is_profit_slipping;
}

#endif

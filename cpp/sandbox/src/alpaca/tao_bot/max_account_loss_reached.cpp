#ifndef ALPACA__TAO_BOT_max_account_loss_reached
#define ALPACA__TAO_BOT_max_account_loss_reached

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Alpaca::TaoBot

#include <regex>  // std::regex, std::regex_search, std::smatch
#include <string> // std::string, std::stod

bool Alpaca::TaoBot::max_account_loss_reached() {
  if (!this->backtest.is_active ||
      !std::regex_search(this->backtest.config.api_key_id,
                         std::regex("-act_(.+)__(.+)$"))) {
    return false;
  }

  double loss_ratio = this->MAX_ACCOUNT_LOSS_RATIO;

  if (this->backtest.is_active) {
    std::smatch match;

    std::regex_search(this->backtest.config.api_key_id, match,
                      std::regex("-act_(.+)__(.+)$"));

    if (match.size() < 3) {
      return false;
    }

    const std::string ratio_string =
        std::regex_replace(match[2].str(), std::regex("_"), ".");

    loss_ratio = -1 * (std::stod(ratio_string) / 100.0);
  }

  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const double current_profit_ratio =
      exit_prices_.current_profit / this->account_snapshot.original_equity;

  return current_profit_ratio <= loss_ratio;
}

#endif

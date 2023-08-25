#ifndef ALPACA__TAO_BOT_max_account_loss_reached
#define ALPACA__TAO_BOT_max_account_loss_reached

#include "build_account_exit_prices.cpp" // build_account_exit_prices
#include "tao_bot.h"                     // Alpaca::TaoBot

#include <regex>  // std::regex, std::regex_search, std::smatch
#include <string> // std::string, std::stod

bool Alpaca::TaoBot::max_account_loss_reached() {
  const account_exit_prices_t exit_prices_ = build_account_exit_prices();

  const double current_max_loss_ratio =
      (this->account_snapshot.min_equity -
       this->account_snapshot.original_equity) /
      this->account_snapshot.original_equity;

  if (this->backtest.is_active &&
      !this->backtest.config.account_max_stop_loss) {
    return false;
  }

  if (current_max_loss_ratio <= this->MEGA_MAX_ACCOUNT_LOSS_RATIO) {
    return true;
  }

  double loss_ratio =
      this->MAX_ACCOUNT_LOSS_RATIOS[this->api_client.config.api_key];

  if (!loss_ratio) {
    loss_ratio = this->MAX_ACCOUNT_LOSS_RATIO;
  }

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

  return current_max_loss_ratio <= loss_ratio;
}

#endif

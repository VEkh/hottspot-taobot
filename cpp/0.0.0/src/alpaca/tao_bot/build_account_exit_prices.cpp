#ifndef ALPACA__TAO_BOT_build_account_exit_prices
#define ALPACA__TAO_BOT_build_account_exit_prices

#include "account_profit_expanding_trailing_stop_ratio.cpp" // account_profit_expanding_trailing_stop_ratio
#include "tao_bot.h"                                        // Alpaca::TaoBot
#include "target_account_profit_ratio.cpp" // target_account_profit_ratio

Alpaca::TaoBot::account_exit_prices_t
Alpaca::TaoBot::build_account_exit_prices() {
  const double current_equity = this->account_snapshot.equity;

  double target_account_profit_ratio_ = target_account_profit_ratio();

  if (this->backtest.is_active) {
    std::smatch match;

    std::regex_search(this->backtest.config.api_key_id, match,
                      std::regex("-act_(.+)__(.+)$"));

    if (match.size() > 2) {
      const std::string ratio_string =
          std::regex_replace(match[1].str(), std::regex("_"), ".");

      target_account_profit_ratio_ = (std::stod(ratio_string) / 100.0);
    }
  }

  const double max_profit = this->account_snapshot.max_equity -
                            this->account_snapshot.original_equity;

  const double target_profit_cash =
      (this->account_snapshot.original_equity * target_account_profit_ratio_);

  const double target_max_profit =
      (this->account_snapshot.original_equity *
       (target_account_profit_ratio_ +
        this->TARGET_ACCOUNT_PROFIT_TRAILING_STOP));

  const double current_profit =
      current_equity - this->account_snapshot.original_equity;

  const double max_profit_ratio =
      max_profit / this->account_snapshot.original_equity;

  const double trailing_stop_cash =
      this->account_snapshot.original_equity *
      account_profit_expanding_trailing_stop_ratio(
          this->account_snapshot.max_equity -
          this->account_snapshot.original_equity);

  const double stop_profit_loss = max_profit - trailing_stop_cash;

  return {
      .current_profit = current_profit,
      .max_profit = max_profit,
      .stop_profit_loss = stop_profit_loss,
      .target_account_profit = target_profit_cash,
      .target_max_profit = target_max_profit,
  };
}

#endif

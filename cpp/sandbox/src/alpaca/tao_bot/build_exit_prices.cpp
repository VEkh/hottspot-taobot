#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

#include <regex> // std::regex, std::regex_replace, std::regex_search, std::smatch
#include <string> // std::string, std::stod

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->one_sec_variance_avgs.running;

  const double trailing_stop_profit_ratio = 1 / 1.1;
  double max_loss_coefficient = -62.5;
  double stop_profit_stop_loss_ratio = 2.5;

  if (this->backtest.is_active) {
    std::smatch l_match;
    std::smatch p_match;

    std::regex_search(this->backtest.config.api_key_id, l_match,
                      std::regex("__(.+)$"));

    std::regex_search(this->backtest.config.api_key_id, p_match,
                      std::regex("^backtest_(.+)__"));

    if (l_match.size() > 1) {
      const std::string loss_coefficient_string =
          std::regex_replace(l_match[1].str(), std::regex("_"), ".");

      max_loss_coefficient = -1 * std::stod(loss_coefficient_string);
    }

    if (p_match.size() > 1) {
      if (p_match[1].str() == "no_stop_profit") {
        stop_profit_stop_loss_ratio = 99999;
      } else {
        const std::string ratio_string =
            std::regex_replace(p_match[1].str(), std::regex("_"), ".");

        stop_profit_stop_loss_ratio = std::stod(ratio_string);
      }
    }
  }

  const double max_loss = max_loss_coefficient * static_one_sec_variance;
  const double stop_profit = abs(stop_profit_stop_loss_ratio * max_loss);

  const double min_profit = stop_profit / trailing_stop_profit_ratio;

  const double trailing_stop_profit =
      this->open_order_ptr->max_profit * trailing_stop_profit_ratio;

  exit_prices_t out = {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };

  return out;
}

#endif

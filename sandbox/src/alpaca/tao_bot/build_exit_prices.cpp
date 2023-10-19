#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

#include <regex> // std::regex, std::regex_replace, std::regex_search, std::smatch
#include <string> // std::string, std::stod

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->avg_one_sec_variances.running;

  const double trailing_stop_profit_ratio = 1 / 1.1;
  double max_loss_coefficient = -this->EXCESS_TRIGGER_BUFFER_COEFFICIENT;
  double stop_profit_stop_loss_ratio = 2.5;

  if (this->backtest.is_active) {
    std::smatch match;
    const std::string id = this->backtest.config.api_key_id;

    std::regex_search(id, match, std::regex("-pos_(.+)__(.+)-\\w+")) ||
        std::regex_search(id, match, std::regex("-pos_(.+)__(.+)$"));

    if (match.size() > 2) {
      if (match[1].str() == "no_stop_profit") {
        stop_profit_stop_loss_ratio = 99999;
      } else {
        const std::string ratio_string =
            std::regex_replace(match[1].str(), std::regex("_"), ".");

        stop_profit_stop_loss_ratio = std::stod(ratio_string);
      }

      const std::string loss_coefficient_string =
          std::regex_replace(match[2].str(), std::regex("_"), ".");

      max_loss_coefficient = -1 * std::stod(loss_coefficient_string);
    }
  }

  const double max_loss = max_loss_coefficient * static_one_sec_variance;
  const double stop_profit = abs(stop_profit_stop_loss_ratio * max_loss);

  const double min_profit = stop_profit / trailing_stop_profit_ratio;

  const double trailing_stop_profit =
      this->open_order_ptr->max_profit * trailing_stop_profit_ratio;

  return {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };
}

#endif

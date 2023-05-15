#ifndef ALPACA__TAO_BOT_read_price_movement
#define ALPACA__TAO_BOT_read_price_movement

#include "tao_bot.h" // Alpaca::TaoBot

#include <regex>  // std::regex, std::smatch
#include <string> // std;:string, std::stoi

void Alpaca::TaoBot::read_price_movement() {
  if (!this->backtest.should_exec_slow_query(this->current_epoch)) {
    return;
  }

  int timestamp_lower_bound_interval_days = 45;

  if (this->backtest.is_active) {
    std::smatch match;
    const std::string id = this->backtest.config.api_key_id;

    if (std::regex_search(id, match, std::regex("-one_sec_(.+)$"))) {
      timestamp_lower_bound_interval_days = std::stoi(match[1].str());
    }
  }

  this->avg_one_sec_variances =
      this->quoter.db_quote.get_avg_one_sec_variances({
          .symbol = this->symbol,
          .timestamp_lower_bound_interval_days =
              timestamp_lower_bound_interval_days,
          .timestamp_upper_bound = this->current_epoch,
      });
}

#endif

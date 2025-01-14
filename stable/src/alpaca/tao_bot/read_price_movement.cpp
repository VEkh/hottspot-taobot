#ifndef ALPACA__TAO_BOT_read_price_movement
#define ALPACA__TAO_BOT_read_price_movement

#include "tao_bot.h" // Alpaca::TaoBot

#include <regex>  // std::regex, std::smatch
#include <string> // std;:string, std::stoi

void Alpaca::TaoBot::read_price_movement() {
  if (!this->backtest.should_exec_slow_query(this->current_epoch)) {
    return;
  }

  const avg_one_sec_variances_t new_avg_one_sec_variances =
      this->quoter.db_quote.get_avg_one_sec_variances({
          .symbol = this->symbol,
          .timestamp_upper_bound = this->current_epoch,
      });

  if (new_avg_one_sec_variances.running) {
    this->avg_one_sec_variances = new_avg_one_sec_variances;
  }
}

#endif

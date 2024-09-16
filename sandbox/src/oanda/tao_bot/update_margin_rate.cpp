#ifndef OANDA__TAO_BOT_update_margin_rate
#define OANDA__TAO_BOT_update_margin_rate

#include "fetch_and_persist_margin_rates.cpp" // fetch_and_persist_margin_rates
#include "lib/formatted.cpp"                  // Formatted
#include "tao_bot.h"                          // Alpaca::TaoBot, margin_rate_t
#include <stdexcept>                          // std::out_of_range
#include <string>                             // std::string

void Oanda::TaoBot::update_margin_rate() {
  if (!this->backtest.is_active) {
    fetch_and_persist_margin_rates({this->symbol});
  }

  this->margin_rate = this->db_margin_rate.get(this->symbol);

  if (!this->margin_rate.multiplier) {
    const std::string error_message = Formatted::error_message(
        std::string(
            "[OANDA__TAO_BOT_update_margin_rate]: No margin rate exists for ") +
        this->symbol);

    throw std::out_of_range(error_message);
  }
}

#endif

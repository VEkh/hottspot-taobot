#ifndef ALPACA__TAO_BOT_ensure_market_is_open
#define ALPACA__TAO_BOT_ensure_market_is_open

#include "lib/formatted.cpp" // Formatted::error_message
#include "tao_bot.h"         // Alpaca::TaoBot
#include <stdexcept>         // std::runtime_error
#include <string>            // std::string

void Alpaca::TaoBot::ensure_market_is_open() {
  if (this->market_availability.is_holiday(this->current_epoch)) {
    const std::string message = Formatted::error_message(
        "🎉 Today is a holiday! The markets are closed, so go have "
        "fun yabish!! 🥳 ");

    throw std::runtime_error(message);
  }
}

#endif

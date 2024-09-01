#ifndef OANDA__TAO_BOT_ensure_spread_limit
#define OANDA__TAO_BOT_ensure_spread_limit

#include "lib/formatted.cpp" // Formatted::error_message
#include "spread_limit.cpp"  // spread_limit
#include "tao_bot.h"         // Oanda::TaoBot
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void Oanda::TaoBot::ensure_spread_limit() {
  if (spread_limit() <= 0) {
    const std::string message = Formatted::error_message(
        "Must specify a spread limit for <" + this->symbol + ">");

    throw std::invalid_argument(message);
  }
}

#endif
